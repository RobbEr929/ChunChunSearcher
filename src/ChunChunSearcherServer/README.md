## ChunChunSearcherServer
用PHP做的云平台接口，用于ChunChunSearcher的云服务调用。

数据库使用的MySQL。


## 以下为框架改编者的叙述
### Laravel6

#### 对Laravel6进行了小修改（也不算是修改,就算是把常用的东西整合上去）

#### 1、返回接口统一
    文件位置：
        App\Helpers\json.php;
    使用：
        json_success($msg, $data);
        json_fail($msg, $data);
#### 2、Monolog\Logger整合
    文件位置：
        App\Helpers\logger.php;
    使用：
        logInfo($title, [$msg]);
        logWarning($title, [$msg]);
        logError($title, [$msg]);
        logDebug($title, [$msg]);
#### 3、JWT整合
    文件位置：
        App\Models\User
    使用：
        jwt整合到了auth，使用与auth一样
#### 4、重写了异常处理
    文件位置：
        App\Exceptions\Handler
    
#### 5、整合了Repositories 设计模式
        生成对应文件：
            php artisan init:model-service
        文件位置：
            App\Repositories\*
            App\Facades\*
            App\Providers\RepositoryServiceProvider
        使用：
            use App\Facades\***;
            ***::getFirst()...
        这里封装的方法可以查看:
            App\Traits\RepositoryBaseRepositoryTrait
            App\Repositories\CommonRepository
#### 6、在Helpers中封装了很多方法，也可以自己添加方法
        文件位置：
            App\Helpers\*
#### 7、在 App\Traits\Controller\*下封装了一些公共的Controller方法，需要使用就use
        文件位置：
            App\Traits\Controller\*
        使用：
            use App\Facades\Controller\***;
