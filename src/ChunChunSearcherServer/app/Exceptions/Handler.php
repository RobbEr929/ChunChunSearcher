<?php

namespace App\Exceptions;

use Exception;
use Symfony\Component\HttpKernel\Exception\HttpException;
use Illuminate\Support\Facades\Request;
use Illuminate\Auth\AuthenticationException;
use Illuminate\Foundation\Exceptions\Handler as ExceptionHandler;

class Handler extends ExceptionHandler
{
    /**
     * A list of the exception types that are not reported.
     *
     * @var array
     */
    protected $dontReport = [
        //
    ];

    /**
     * A list of the inputs that are never flashed for validation exceptions.
     *
     * @var array
     */
    protected $dontFlash = [
        'password',
        'password_confirmation',
    ];

    /**
     * Report or log an exception.
     *
     * @param  \Exception $exception
     * @return void
     *
     * @throws \Exception
     */
    public function report(Exception $exception)
    {
        parent::report($exception);
    }

    /**
     * Render an exception into an HTTP response.
     *
     * @param  \Illuminate\Http\Request $request
     * @param  \Exception $exception
     * @return \Symfony\Component\HttpFoundation\Response
     *
     * @throws \Exception
     */
    public function render($request, Exception $exception)
    {
        $error_msg = '服务器错误！';
        if ($exception instanceof HttpException) {
            if ($exception->getStatusCode() == '404') {
                $StatusCode = $exception->getStatusCode();
                $errors = $exception->getMessage();
            } else {
                $StatusCode = 500;
                $errors = $exception->getMessage();
                logError($error_msg, [$errors]);
            }
        } else if ($exception instanceof AuthenticationException) {
            $StatusCode = 403;
            $error_msg = '权限不足！';
            $errors = $exception->getMessage();
        } else {
            $errors = $exception->getMessage();
            $StatusCode = 500;
            logError($error_msg, [$errors]);
        }
        if (Request::ajax()) {
            return json_fail($error_msg, env('APP_DEBUG') ? $errors : null, $StatusCode, $StatusCode);
        } else {
            return env('APP_DEBUG') ?
                parent::render($request, $exception) :
                response()->view('errors.' . $StatusCode, ['errors' => $errors], $StatusCode);
        }
    }
}
