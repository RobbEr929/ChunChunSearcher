<?php

namespace App\Facades;

use Illuminate\Support\Facades\Facade;

/**
 * @method static mixed whereUpdate(array $where, $data)
 * @method static mixed whereInUpdate(array $where, $data)
 * @method static mixed getById($id,$selects = "*")
 * @method static mixed getFirst(array $where, $selects = "*")
 * @method static mixed getFirstWithTrashed(array $where, $selects = "*")
 * @method static mixed getAll()
 * @method static mixed getWhere(array $where, array $orderby=[],$selects = '*')
 * @method static mixed getWhereIn(array $whereIn, $selects = '*')
 * @method static mixed getWhereRaw($whereraw, array $orderby=[],$selects = '*')
 * @method static mixed getPageList($pageNum, $pageSize,array $orderby, $selects = '*')
 * @method static mixed getCount()
 * @method static mixed getPageListWhere($pageNum, $pageSize, array $where,array $orderby,$selects = '*')
 * @method static mixed getCountWhere($where)
 * @method static mixed getPageListWhereRaw($pageNum, $pageSize, $whereRaw,array $orderby,$selects = '*')
 * @method static mixed getCountWhereRaw($whereRaw)
 * @method static mixed batchInsert(array $items)
 * @method static mixed getSelects(array $where, array $orderby, $selects)
 * @method static mixed pagetemp($res,$pageSize, $pageNum,$orderby,$selects='*')
 */
class UserRepository extends Facade
{
    protected static function getFacadeAccessor()
    {
        return 'UserRepository';
    }
}