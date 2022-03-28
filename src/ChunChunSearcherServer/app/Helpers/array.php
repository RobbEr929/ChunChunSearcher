<?php

//把null值处理成字符串中的空值
if ( ! function_exists('deal_null')) {
    function deal_null(array $inputs){
        $arr=[];
        foreach ($inputs as $key=>$input){
            if($input==null&&$input!==0){
                $arr[$key]='';
            }else{
                $arr[$key]=$input;
            }
        }
        return $arr;
    }
}

//返回图片后缀的数组
if ( ! function_exists('exts_image')) {
    function exts_image(){
        return ['jpg','png','gif','jpeg'];
    }
}
//返回文档后缀的数组
if ( ! function_exists('exts_doc')) {
    function exts_doc(){
        return ['doc','docx','xlsx','xls','ppt','pptx'];
    }
}
//返回音频文件后缀的数组
if ( ! function_exists('exts_audio')) {
    function exts_audio(){
        return ['mp3'];
    }
}

if ( ! function_exists('is_image')) {
    function is_image($ext){
        return in_array(strtolower($ext),exts_image());
    }
}
if ( ! function_exists('is_doc')) {
    function is_doc($ext){
        return in_array(strtolower($ext),exts_doc());
    }
}
if ( ! function_exists('is_music')) {
    function is_music($ext){
        return in_array(strtolower($ext),exts_audio());
    }
}
if ( ! function_exists('arrayeval')) {
    function arrayeval($array,$format=false,$level=0){
        $space=$line='';
        if(!$format){
            for($i=0;$i<=$level;$i++){
                $space.="\t";
            }
            $line="\n";
        }
        $evaluate='Array'.$line.$space.'('.$line;
        $comma=$space;
        foreach($array as $key=> $val){
            $key=is_string($key)?'\''.addcslashes($key,'\'\\').'\'':$key;
            $val=!is_array($val)&&(!preg_match('/^\-?\d+$/',$val)||strlen($val) > 12)?'\''.addcslashes($val,'\'\\').'\'':$val;
            if(is_array($val)){
                $evaluate.=$comma.$key.'=>'.arrayeval($val,$format,$level+1);
            }else{
                $evaluate.=$comma.$key.'=>'.$val;
            }
            $comma=','.$line.$space;
        }
        $evaluate.=$line.$space.')';
        return $evaluate;
    }

}

