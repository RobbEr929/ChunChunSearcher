<?php

if ( ! function_exists('obj_info')) {
    /**
     * 返回格式化对象
     * @param $status true or false
     * @param $msg 消息
     * @param null $data 数据
     * @return stdClass
     */
    function obj_info($status,$msg,$data=null){
        $newobj = new stdClass();
        $newobj->status = $status;
        $newobj->msg = $msg;
        if($data!=null){
            $newobj->data=$data;
        }
        return $newobj;
    }
}
if ( ! function_exists('get_ids')) {
    function get_ids($objs,$attr='id'){
        if($objs==null){
            return null;
        }
        $ids=[];
        foreach ($objs as $obj){
            if(is_array($obj)){
                $val=$obj[$attr];
            }else{
                $val=$obj->$attr;
            }
            if(!in_array($val,$ids)){
                array_push($ids,$val);
            }
        }
        return $ids;
    }
}


