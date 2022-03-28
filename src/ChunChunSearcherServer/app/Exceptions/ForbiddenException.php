<?php
/**
 * 无权限异常
 */

namespace App\Exceptions;


class ForbiddenException extends ProgramException
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
        // 没有权限访问
        $message = $this->getMessage() ?: '您没有权限操作';
        $code = $this->getCode() ?: 401;
        $redirect = $this->getRedirect() ?: '/';
        return $request->ajax() || $request->wantsJson()
            ? json_response(1001,$message)
            :response(view('errors.401', compact('code', 'message', 'redirect')), $code);
    }
}