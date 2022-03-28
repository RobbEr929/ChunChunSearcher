<?php namespace App\Repositories;

/**
 * 数据库操作基类，所有表都可以用
 * 通过子类继承来调用
 * 重用
 */

use App\Exceptions\ValidateException;
use App\Traits\Repository\BaseRepositoryTrait;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Validation\Factory;
use Illuminate\Support\Arr;

abstract class CommonRepository
{
    use BaseRepositoryTrait;

    /**
     * 模型实例
     * @var Model
     */
    protected $model;

    /**
     * The validator factory instance.
     * @var \Illuminate\Validation\Factory
     */
    protected $validator;

    /**
     * Create a new instance.
     * @param Model $model
     * @param Factory $validator
     */
    public function __construct(Model $model, Factory $validator)
    {
        $this->model = $model;
        $this->validator = $validator;
    }

    /**
     *  $model->rules规则过滤 （对传入参数的过滤规则，定义在Models下的各类中）
     * @param null $query
     * @return array
     */
    public function rules($query = null)
    {
        $model = $this->model;
        // get rules from the model if set
        if (isset($model->rules)) {
            $rules = $model->rules;
        } else {
            $rules = [];
        }
        // if the there are no rules
        if (!is_array($rules) || !$rules) {
            // return an empty array
            return [];
        }
        // if the query is empty
        if (!$query) {
            // return all of the rules
            return array_filter($rules);
        }
        // return the relevant rules
        return array_filter(Arr::only($rules, $query));
    }

    /**
     * 验证数据  根据上面的验证规则，验证传入的参数是否合法
     * $model->messages如果不合法返回错误消息（错误消息定义再Models下面各类中）
     * @param array $data
     * @param null $rules
     * @param bool $custom
     * @return void
     * @throws ValidateException
     */
    public function validate(array $data, $rules = null, $custom = false)
    {
        if (!$custom) {
            $rules = $this->rules($rules);
        }
        $model = $this->model;
        if (!isset($model->messages)) {
            $model->messages = [];
        }
        $val = $this->validator->make($data, $rules, $model->messages);
        if ($val->fails()) {
            throw new ValidateException(join('<br/>', $val->errors()->all()));
        }
    }

    /**
     * 删除数据，软删除
     * @param int $id
     * @return bool|null
     * @throws ValidateException
     */
    public function destroy($id)
    {
        $result = false;
        if (is_array($id)) { //批量删除
            $items = $this->model->whereIn('id', $id)->get();
            if (count($items) == 0) {
                throw new ValidateException('没有找到这些数据，可能已经删除了！');
            }
            foreach ($items as $item) {
                if (method_exists($this, 'destroyWith')) {
                    $this->destroyWith($item);
                }
                $result = $item->delete();
            }
        } else {
            $item = $this->model->find($id);
            if (!$item) {
                throw new ValidateException('没有找到这条数据，可能已经删除了！');
            }
            if (method_exists($this, 'destroyWith')) {
                $this->destroyWith($item);
            }
            $result = $item->delete();
        }
        return $result;
    }

    /**
     * 恢复数据
     * @param $id
     * @return array
     * @throws ValidateException
     */
    public function restore($id)
    {
        $result = false;
        if (is_array($id)) { //批量恢复
            $items = $this->model->onlyTrashed()->whereIn('id', $id)->get();
            foreach ($items as $item) {
                $result = $item->restore();
                if (method_exists($this, 'restoreWith')) {
                    $this->restoreWith($item);
                }
            }
        } else {
            $item = $this->model->onlyTrashed()->find($id);
            if (!$item) {
                throw new ValidateException('没有找到这条数据，可能已经恢复了！');
            }
            if (method_exists($this, 'restoreWith')) {
                $this->restoreWith($item);
            }
            $result = $item->restore();
        }
        return $result;
    }

    /**
     * 分页
     * @param $pageSize
     * @param string $selects
     * @return mixed
     */
    public function originalPaginate($pageSize, $selects = '*')
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();
        }
        return $model->select($selects)->paginate($pageSize);
    }


    /**
     * 条件分页
     * @param $pageSize
     * @param array $where
     * @param string $selects
     * @return mixed
     */
    public function wherePaginate($pageSize, array $where, $selects = '*')
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();
        }
        return $model->select($selects)->where($where)->paginate($pageSize);
    }
}
