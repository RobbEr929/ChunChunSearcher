<?php
/**
 * Model字段验证异常
 */

namespace App\Exceptions;


class ValidateException extends ProgramException
{
    /**
     * Report the exception.
     *
     * @return void
     */
    public function report()
    {
        //
    }

    /**
     * @param $request
     * @return \Illuminate\Contracts\Routing\ResponseFactory|\Illuminate\Http\JsonResponse|\Illuminate\Http\Response
     */
    public function render($request)
    {
        // 字段验证异常
        $message = $this->getMessage() ?: '字段不符合规格，验证失败';
        $code = $this->getCode() ?: 200;
        $redirect = $this->getRedirect() ?: '/';
        return $request->ajax() || $request->wantsJson() ?
            json_fail($message) :
            response(view('errors.400', compact('code', 'message', 'redirect')), $code);
    }
}