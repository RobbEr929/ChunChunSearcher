<?php
/**
 * 自定义程序异常父类
 */

namespace App\Exceptions;


class ProgramException extends \Exception
{
    protected $redirect;
    function __construct($msg='',$redirect='')
    {
        $this->redirect=$redirect;
        parent::__construct($msg);
    }

    function getRedirect(){
        return $this->redirect;
    }
}