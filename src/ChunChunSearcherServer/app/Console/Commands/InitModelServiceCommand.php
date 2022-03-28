<?php

namespace App\Console\Commands;

use Illuminate\Console\Command;
use Illuminate\Support\Facades\File;

class InitModelServiceCommand extends Command
{
    /**
     * The name and signature of the console command.
     *
     * @var string
     */
    protected $signature = 'init:model-service';

    /**
     * The console command description.
     *
     * @var string
     */
    protected $description = '根据所有Model中table生成相应table的数据库字段配置，以及生成ServiceProvider中需要的Model路径和Repository路径';

    /**
     * Create a new command instance.
     *
     * @return void
     */
    public function __construct()
    {
        parent::__construct();
    }

    /**
     * Execute the console command.
     *
     * @return mixed
     */
    public function handle()
    {
        // 获取所有的Model
        $files = File::allFiles(app_path('Models'));

        $config = [];

        foreach ($files as $file) {
            $modelName = str_replace(
                [app_path(), '/', '.php'],
                ['App', '\\', ''],
                $file->getRealPath()
            );
            // 根据model名称实例化，只有设置了table的才生成
            $model = new $modelName();
            if (isset($model->table)) {
                // 生成Model中所需配置
                $this->generateColumns($config, $model);
                // 生成ServiceProvider中所需配置
                $this->generateRepositories($config, $modelName);
            }
        }

        //生成文件
        $path = config_path('model-service.php');
        $configStr = "<?php\r\n\r\n return " . arrayeval($config, false) . ";";
        File::put($path, $configStr);

        $this->info("$path 生成成功！");
    }

    /*
     生成columns
     'columns'=>
        [
            'rbac_permissions'=>['id','name','guard_name','created_at','updated_at']
        ]
     */
    private function generateColumns(&$config, $model)
    {
        // 生成Model中所需配置
        $tableName = $model->table;
        $columns = \Illuminate\Support\Facades\Schema::getColumnListing($tableName);
        $config['columns'][$tableName] = $columns;
    }

    /*
     生成repositories
     'repositories'=>
        [
            'PermissionRepository'=>
                [
                    'model'=>'App\\Models\\Permission',
			        'repository'=>'App\\Repositories\\PermissionRepository'
                ]
        ]
    */
    private function generateRepositories(&$config, $modelName)
    {
        // 生成ServiceProvider中所需配置
        // 例如：UserRepository
        $repositoryName = str_replace('App\\Models\\', '', $modelName) . 'Repository';
        $repository = 'App\Repositories\\' . $repositoryName;

        $newRepositoryName = trim(strrchr($repositoryName, '\\'), '\\');
        if (empty($newRepositoryName)) {
            $newRepositoryName = $repositoryName;
        }

        // 控制台显示生成的Repository
        if (class_exists($repository)) {
            $config['repositories'][$newRepositoryName]['model'] = $modelName;
            $config['repositories'][$newRepositoryName]['repository'] = $repository;
            // 生成对应的Facade
            $this->generateFacade($newRepositoryName);
        } else {
            $facacdesPath = app_path("Repositories");
            $path = $repository . '.php';
            if (!File::exists($facacdesPath)) {
                File::makeDirectory($facacdesPath);
            }
            $phpStr = "<?php namespace App\Repositories;
 /**
 * Class $repositoryName
 * @package App\Repositories
 */           
class $repositoryName extends CommonRepository {

}";
            File::put($path, $phpStr);
            $this->info("$path 生成成功！");
            $config['repositories'][$newRepositoryName]['model'] = $modelName;
            $config['repositories'][$newRepositoryName]['repository'] = $repository;
            // 生成对应的Facade
            $this->generateFacade($newRepositoryName);
        }
    }

    /**
     * 生产Facades目录下文件
     */
    private function generateFacade($repositoryName)
    {


        //生成文件
        $facacdesPath = app_path("Facades");
        $path = $facacdesPath . "\\$repositoryName.php";
        if (!File::exists($facacdesPath)) {
            File::makeDirectory($facacdesPath);
        }
        $phpStr = "<?php

namespace App\Facades;

use Illuminate\Support\Facades\Facade;

/**
 * @method static mixed whereUpdate(array \$where, \$data)
 * @method static mixed whereInUpdate(array \$where, \$data)
 * @method static mixed getById(\$id,\$selects = \"*\")
 * @method static mixed getFirst(array \$where, \$selects = \"*\")
 * @method static mixed getFirstWithTrashed(array \$where, \$selects = \"*\")
 * @method static mixed getAll()
 * @method static mixed getWhere(array \$where, array \$orderby=[],\$selects = '*')
 * @method static mixed getWhereIn(array \$whereIn, \$selects = '*')
 * @method static mixed getWhereRaw(\$whereraw, array \$orderby=[],\$selects = '*')
 * @method static mixed getPageList(\$pageNum, \$pageSize,array \$orderby, \$selects = '*')
 * @method static mixed getCount()
 * @method static mixed getPageListWhere(\$pageNum, \$pageSize, array \$where,array \$orderby,\$selects = '*')
 * @method static mixed getCountWhere(\$where)
 * @method static mixed getPageListWhereRaw(\$pageNum, \$pageSize, \$whereRaw,array \$orderby,\$selects = '*')
 * @method static mixed getCountWhereRaw(\$whereRaw)
 * @method static mixed batchInsert(array \$items)
 * @method static mixed getSelects(array \$where, array \$orderby, \$selects)
 * @method static mixed pagetemp(\$res,\$pageSize, \$pageNum,\$orderby,\$selects='*')
 */
class $repositoryName extends Facade
{
    protected static function getFacadeAccessor()
    {
        return '$repositoryName';
    }
}";
        File::put($path, $phpStr);

        $this->info("$path 生成成功！");

    }
}
