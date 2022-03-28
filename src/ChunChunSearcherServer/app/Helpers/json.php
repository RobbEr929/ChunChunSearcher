<?php

if (!function_exists('json_response')) {
    /**
     * 返回给页面json的信息，ajax操作时返回的提示信息
     * @param $code
     * @param $msg
     * @param null $data
     * @param int $status
     * @return \Illuminate\Http\JsonResponse
     */
    function json_response($code, $msg, $data = null, $status = 200)
    {
        return response()->json(array('code' => $code, 'msg' => $msg, 'data' => $data), $status);
    }
}
if (!function_exists('json_success')) {
    function json_success($msg = '操作成功!', $data = null, $code = 0, $StatusCode = 200)
    {
        return json_response($code, $msg, $data, $StatusCode);
    }
}
if (!function_exists('json_fail')) {
    function json_fail($msg = '操作失败!', $data = null, $code = 1, $StatusCode = 200)
    {
        return json_response($code, $msg, $data, $StatusCode);
    }
}
if (!function_exists('json_page')) {
    /**
     * @param $data
     * @param $count
     * @param string $msg
     * @param int $code
     * @return \Illuminate\Http\JsonResponse
     */
    function json_page($data, $count, $msg = '', $code = 0)
    {
        return response()->json(array('data' => $data, 'count' => $count, 'code' => $code, 'msg' => $msg));
    }
}


if (!function_exists('to_json_response')) {
    /**
     * 将对象转换成，页面json的信息，ajax操作时返回的提示信息
     * @param $obj
     * @return \Illuminate\Http\JsonResponse
     */
    function to_json_response($obj)
    {
        $data = isset($obj->data) ? $obj->data : null;
        if (isset($obj->status) && $obj->status) {
            return json_success($obj->msg, $data);
        } else {
            return json_fail($obj->msg, $data);
        }
    }
}

if (!function_exists('json_success_fail')) {
    /**
     * 将对象转换成，页面json的信息，ajax操作时返回的提示信息
     * @param $model
     * @param null $msg1
     * @param null $msg2
     * @return string
     */
    function json_success_fail($model, $msg1 = null, $msg2 = null)
    {
        if ($model) {
            return json_success($msg2 === null ? '操作成功！' : $msg2, $model);
        } else {
            return json_fail($msg1 === null ? '操作失败！' : $msg1);
        }
    }
}
