<?php
namespace App\Traits\Repository;

trait BaseRepositoryTrait
{

    /**
     * 根据条件批量更新多条数据
     * $this->whereUpdate(array('id'=>1),array('status'=>2));
     * @param $where
     * @param $data
     * @return mixed
     */
    public function whereUpdate(array $where, $data)
    {
        return $this->model->where($where)->update($data);
    }

    /**
     * UserRepository::whereInUpdate(['id'=>[1,4,5]],['status'=>$val]);
     * @param array $where
     * @param $data
     * @return bool
     */
    public function whereInUpdate(array $where, $data)
    {
        $res=$this->model;
        foreach ($where as $key=>$vals){
            $res=$res->whereIn($key,$vals);
        }
        return $res->update($data);
    }


    /**
     * 通过id获得数据
     * @param $id
     * @param string|array $selects
     * @return mixed
     */
    public function getById($id,$selects = "*")
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();
        }
        return $model->select($selects)->find($id);
    }

    /**
     * 通过id获得数据
     * @param array $where
     * @param string $selects
     * @return Model|null|static
     */
    public function getFirst(array $where, $selects = "*")
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();
        }

        $models=$model->where($where)->select($selects)->first();
        if($models!=null){
            return $models;
        }
        return null;
    }

    /**
     * 通过id获得数据
     * @param array $where
     * @param string $selects
     * @return Model|null|statiw
     */
    public function getFirstWithTrashed(array $where, $selects = "*")
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();
        }

        $models=$model->withTrashed()->where($where)->select($selects)->first();
        if($models!=null){
            return $models;
        }
        return null;
    }

    /**
     * 获取所有数据
     * @return \Illuminate\Database\Eloquent\Collection|static[]
     */
    public function getAll($selects = '*')
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();

        }
        return $model->select($selects)->get();
    }

    /**
     * 根据获得数据
     * @param array $where 查询条件  例:array('id'=>'1')
     * @param array $orderby 排序  例:array('id','asc')
     * @param string $selects
     * @return mixed
     */
    public function getWhere(array $where, array $orderby=[],$selects = '*')
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();
        }

        $res=$model->where($where);
        if(count($orderby)>0){
            $res=$res->orderBy($orderby[0], $orderby[1]);
        }
        return $res->select($selects)->get();
    }

    /**
     * 根据获得数据
     * @param array $whereIn 查询条件  例:['id'=>array('id','1')]
     * @param string $selects
     * @return mixed
     */
    public function getWhereIn(array $whereIn, $selects = '*')
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();
        }
        $key=key($whereIn);
        return $model->whereIn($key,$whereIn[$key])->select($selects)->get();
    }

    /**
     * 根据获得数据
     * @param array $whereraw 查询条件  例:'id'='1'
     * @param array $orderby 排序  例:array('id','asc')
     * @param string $selects
     * @return mixed
     */
    public function getWhereRaw($whereraw, array $orderby=[],$selects = '*')
    {

        $model = $this->model;

        $res=$model->whereRaw($whereraw);
        if ($selects == '*') {
            $selects = $model->getColumns();
        }
        if(count($orderby)>0){
            $res=$res->orderBy($orderby[0], $orderby[1]);
        }
        return $res=$res->select($selects)->get();
    }

    /**
     * 获得分页数据
     * 例：$data["rows"]=UserRepository::getPageList(1,15,['id','desc'],1);
     * @param $pageNum 页码
     * @param $pageSize 每页数据量
     * @param array $orderby 根据什么排序
     * @param string $selects
     * @return mixed
     */
    public function getPageList($pageNum, $pageSize,array $orderby, $selects = '*')
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();
        }
        return $model->select($selects)
            ->orderBy($orderby[0], $orderby[1])
            ->skip($pageSize * ($pageNum - 1))
            ->take($pageSize)->get();
    }

    /**
     * 获得记录条数
     * @return mixed
     */
    public function getCount()
    {
        return $this->model->count();
    }

    /**
     * 分页条件查询
     * @param $pageNum
     * @param $pageSize
     * @param $where
     * @param string $selects
     * @return mixed
     */
    public function getPageListWhere($pageNum, $pageSize, array $where,array $orderby,$selects = '*')
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();
        }
        return $model->select($selects)
            ->where($where)
            ->orderBy($orderby[0], $orderby[1])->skip($pageSize * ($pageNum - 1))->take($pageSize)->get();
    }

    /**
     * 根据条件查询总数量
     * @param $where
     * @return mixed
     */
    public function getCountWhere($where)
    {
        return $this->model->where($where)->count();
    }

    /**
     * 分页条件查询
     * @param $pageNum
     * @param $pageSize
     * @param $whereRaw
     * @param string $selects
     * @return mixed
     */
    public function getPageListWhereRaw($pageNum, $pageSize, $whereRaw,array $orderby,$selects = '*')
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();
        }
        $res=$model->select($selects)
            ->whereRaw($whereRaw);
            if(count($orderby)>0){
                $res=$res->orderBy($orderby[0], $orderby[1]);
            }
        return $res->skip($pageSize * ($pageNum - 1))->take($pageSize)->get();
    }

    /**
     * 根据条件查询总数量
     * @param $whereRaw
     * @return mixed
     */
    public function getCountWhereRaw($whereRaw)
    {
        return $this->model->whereRaw($whereRaw)->count();
    }

    /**
     * 批量插入数据
     * @param array $items 例:array(
     * array('email' => 'taylor@example.com', 'votes' => 0),
     * array('email' => 'dayle@example.com', 'votes' => 0),)
     * @return mixed
     */
    public function batchInsert(array $items)
    {
        return $this->model->insert($items);
    }

    /**
     * 查询指定几个字段,得到数据集合
     * @param array $where where查询条件  例:array('id','1')
     * @param array $orderby 排序  例:array('id','asc')
     * @param $selects 要查询的字段  例:array('id','name')
     * @return mixed
     */
    public function getSelects(array $where, array $orderby, $selects)
    {
        return $this->model->where($where)
            ->orderBy($orderby[0], $orderby[1])
            ->select($selects)->get();
    }

    /**
     * 获取分的sql
     * @param $selects
     * @param $res
     * @param $orderby
     * @param $pageSize
     * @param $pageNum
     * @return mixed
     */
    public function pagetemp($res,$pageSize, $pageNum,$orderby,$selects='*')
    {
        $model = $this->model;
        if ($selects == '*') {
            $selects = $model->getColumns();
        }
        $res = $res->select($selects);
        if(is_array($orderby)&&count($orderby)==2){
            $res = $res->orderBy($orderby[0], $orderby[1]);
        }
        $res = $res->skip($pageSize * ($pageNum - 1))
            ->take($pageSize)->get($selects);
        return $res;
    }
}
