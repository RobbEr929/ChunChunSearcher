<?php

namespace App\Traits\Model;


use Illuminate\Support\Facades\Cache;
use Illuminate\Support\Facades\Schema;

trait BaseModelTrait
{
    /**
     * 查询的字段
     * @return \Illuminate\Config\Repository|mixed
     */
    public function getColumns()
    {
        if (!empty($this->table)) {
            $tableName = $this->table;
        }
        if (!empty($tableName)) {
            return config('model-service.columns.' . $tableName);
        } else {
            return null;
        }
    }

    /**
     * 重载getFillable
     * @return array
     */
    public function getFillable()
    {
        $newColumns = [];
        if (isset($this->table)) {
            $tableName = $this->table;
        }
        if (!empty($tableName)) {
            $columns = config('model-service.columns.' . $tableName);
        }
        if (isset($columns)) {
            foreach ($columns as $item) {
                if (!in_array($item, ['id', 'deleted_at', 'created_at', 'updated_at'])) {
                    array_push($newColumns, $item);
                }
            }
        }
        return $newColumns;
    }
}
