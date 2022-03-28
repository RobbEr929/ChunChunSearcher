<?php

if (!function_exists('empty2zero')) {
    function empty2zero($str)
    {
        if (empty($str)) {
            return 0;
        } else {
            return $str;
        }
    }
}

if (!function_exists('password_score')) {
    /**
     * 设置一个密码强度等级规则，依次返回不同等级，返回的值越大，代表密码复杂度越强
     * @param $str
     * @return int 5个级别
     */
    function password_score($str)
    {
        $score = 0;
        if (strlen($str) < 8) {
            return 0;
        }

        if (preg_match("/[0-9]+/", $str)) {
            $score++;
        }

        if (preg_match("/[a-z]+/", $str)) {
            $score++;
        }
        if (preg_match("/[A-Z]+/", $str)) {
            $score++;
        }
        if (preg_match("/\W/", $str)) {
            $score++;
        }
        if (strlen($str) >= 12) {
            $score++;
        }
        if (preg_match("/[0-9]{3,}/", $str)) {
            $score++;
        }
        if (preg_match("/[a-z]{3,}/", $str)) {
            $score++;
        }
        if (preg_match("/[A-Z]{3,}/", $str)) {
            $score++;
        }
        if (preg_match("/[_|\-|+|=|*|!|@|#|$|%|^|&|(|)]+/", $str)) {
            $score += 2;
        }
        if (preg_match("/[_|\-|+|=|*|!|@|#|$|%|^|&|(|)]{3,}/", $str)) {
            $score++;
        }
        if (strlen($str) >= 10) {
            $score++;
        }
        return $score;
    }
}


/**
 *  根据身份证号码获取性别
 *  author:xiaochuan
 * @param string $idcard 身份证号码
 * @return int $sex 性别 1男 2女 0未知
 */
if (!function_exists('get_sex')) {
    function get_sex($idcard)
    {
        if (empty($idcard)) return null;
        $sexint = (int)substr($idcard, 16, 1);
        return $sexint % 2 === 0 ? '女' : '男';
    }
}

/**
 *  根据身份证号码获取生日
 *  author:xiaochuan
 * @param string $idcard 身份证号码
 * @return $birthday
 */
if (!function_exists('get_birthday')) {
    function get_birthday($idcard)
    {
        if (empty($idcard)) return null;
        $bir = substr($idcard, 6, 8);
        $year = substr($bir, 0, 4);
        $month = substr($bir, 4, 2);
        $day = substr($bir, 6, 2);
        return $year . "-" . $month . "-" . $day;
    }
}
/**
 *  根据身份证号码计算年龄
 *  author:xiaochuan
 * @param string $idcard 身份证号码
 * @return int $age
 */
if (!function_exists('get_age')) {
    function get_age($idcard)
    {
        if (empty($idcard)) return null;
        #  获得出生年月日的时间戳
        $date = strtotime(substr($idcard, 6, 8));
        #  获得今日的时间戳
        $today = strtotime('today');
        #  得到两个日期相差的大体年数
        $diff = floor(($today - $date) / 86400 / 365);
        #  strtotime加上这个年数后得到那日的时间戳后与今日的时间戳相比
        $age = strtotime(substr($idcard, 6, 8) . ' +' . $diff . 'years') > $today ? ($diff + 1) : $diff;
        return $age;
    }
}
//判断身份证号
if (!function_exists('is_idcard')) {
    function is_idcard($id)
    {
        $id = strtoupper($id);
        $regx = "/(^\d{15}$)|(^\d{17}([0-9]|X)$)/";
        $arr_split = array();
        if (!preg_match($regx, $id)) {
            return FALSE;
        }
        if (15 == strlen($id)) //检查15位
        {
            $regx = "/^(\d{6})+(\d{2})+(\d{2})+(\d{2})+(\d{3})$/";

            @preg_match($regx, $id, $arr_split);
            //检查生日日期是否正确
            $dtm_birth = "19" . $arr_split[2] . '/' . $arr_split[3] . '/' . $arr_split[4];
            if (!strtotime($dtm_birth)) {
                return FALSE;
            } else {
                return TRUE;
            }
        } else      //检查18位
        {
            $regx = "/^(\d{6})+(\d{4})+(\d{2})+(\d{2})+(\d{3})([0-9]|X)$/";
            @preg_match($regx, $id, $arr_split);
            $dtm_birth = $arr_split[2] . '/' . $arr_split[3] . '/' . $arr_split[4];
            if (!strtotime($dtm_birth)) //检查生日日期是否正确
            {
                return FALSE;
            } else {
                //检验18位身份证的校验码是否正确。
                //校验位按照ISO 7064:1983.MOD 11-2的规定生成，X可以认为是数字10。
                $arr_int = array(7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2);
                $arr_ch = array('1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2');
                $sign = 0;
                for ($i = 0; $i < 17; $i++) {
                    $b = (int)$id[$i];
                    $w = $arr_int[$i];
                    $sign += $b * $w;
                }
                $n = $sign % 11;
                $val_num = $arr_ch[$n];
                if ($val_num != substr($id, 17, 1)) {
                    return FALSE;
                }
                else {
                    return TRUE;
                }
            }
        }

    }
}
//判断学籍号
if (!function_exists('is_student_id')) {
    function is_student_id($id)
    {
        if (19 != strlen($id)) {
            return false;
        }
        $id = strtoupper($id);
        $zms = ['G', 'J', 'L', 'g', 'j', 'l'];
        $firstZM = substr($id, 0, 1);
        if (!in_array($firstZM, $zms)) {
            return false;
        }
        $q6 = substr($id, 1, 6);
        if (!((int)$q6 > 1)) {
            return false;
        }
        $year = (int)substr($id, 7, 4);
        $currYear = (int)date('Y');
        if ($year < 1970 || $year > $currYear - 3) {
            return false;
        }
        $month = (int)substr($id, 11, 2);
        $day = (int)substr($id, 13, 2);
        if ($month < 1 || $month > 12 || $day < 0 || $day > 31) {
            return false;
        }

        if (strtoupper($firstZM) == 'G') {
            $idcard = substr($id, 1);
            if (!is_idcard($idcard)) {
                return false;
            }
        }

        return true;
    }
}

if (!function_exists('xss_filter')) {
    //php防注入和XSS攻击过滤.
    function xss_filter(&$arr, $strict = false)
    {
        $ra = Array('/([\x00-\x08,\x0b-\x0c,\x0e-\x19])/', '/script/', '/javascript/', '/vbscript/', '/expression/', '/applet/', '/meta/', '/xml/', '/blink/', '/link/', '/style/', '/embed/', '/object/',
            '/frame/', '/layer/', '/title/', '/bgsound/', '/base/', '/onload/', '/onunload/', '/onchange/', '/onsubmit/', '/onreset/', '/onselect/', '/onblur/', '/onfocus/', '/onabort/',
            '/onkeydown/', '/onkeypress/', '/onkeyup/', '/onclick/', '/ondblclick/', '/onmousedown/', '/onmousemove/', '/onmouseout/', '/onmouseover/', '/onmouseup/', '/onunload/');
        if (is_array($arr)) {
            foreach ($arr as $key => $value) {
                if (!is_array($value)) {
                    if (!get_magic_quotes_gpc()) { //不对magic_quotes_gpc转义过的字符使用addslashes(),避免双重转义。
                        $value = addslashes($value); //给单引号（'）、双引号（"）、反斜线（\）与 NUL（NULL 字符）加上反斜线转义
                    }
                    if ($strict) { //严格模式过滤所有的标签
                        $value = preg_replace($ra, '', $value); //删除非打印字符，粗暴式过滤xss可疑字符串
                        $value = strip_tags($value);//函数剥去字符串中的 HTML、XML 以及 PHP 的标签。
                    }
                    $arr[$key] = e($value); //去除 HTML 和 PHP 标记并转换为 HTML 实体
                } else {
                    xss_filter($arr[$key]);
                }
            }
        }
    }
}

if (!function_exists('d_sql_injection')) {
    //防止sql注入
    function d_sql_injection($keyword)
    {
        $keyword = addslashes($keyword);
        return $keyword = preg_replace('/&((#(\d{3,5}|x[a-fA-F0-9]{4}));)/', '&\\1', $keyword);
    }
}

if (!function_exists('hash_encode')) {
    function hash_encode($id)
    {
        $hashids = new \Hashids\Hashids('epassportslat', 20);
        return $hashids->encode($id);
    }
}

if (!function_exists('hash_decode')) {
    /**
     * @param $openid
     * @return array|mixed
     * @throws \App\Exceptions\ValidateException
     */
    function hash_decode($openid)
    {
        try {
            $hashids = new \Hashids\Hashids('epassportslat', 20);
            $id = $hashids->decode($openid);
            if (is_array($id) && count($id) > 0) {
                $id = $id[0];
            }
            return $id;
        } catch (\Exception $e) {
            throw new \App\Exceptions\ValidateException('数据有误！');
        }
    }
}

if (!function_exists('get_vcode')) {
    function get_vcode($num = 4, $fontsize = 14, $width = 80, $height = 30)
    {
        $image = imagecreatetruecolor($width, $height);    //1>设置验证码图片大小的函数
        //5>设置验证码颜色 imagecolorallocate(int im, int red, int green, int blue);
        $bgcolor = imagecolorallocate($image, 255, 255, 255); //#ffffff
        //6>区域填充 int imagefill(int im, int x, int y, int col) (x,y) 所在的区域着色,col 表示欲涂上的颜色
        imagefill($image, 0, 0, $bgcolor);
        //10>设置变量
        $captcha_code = "";
        //7>生成随机的字母和数字
        for ($i = 0; $i < $num; $i++) {
            //设置字体大小
            //设置字体颜色，随机颜色
            $fontcolor = imagecolorallocate($image, rand(0, 120), rand(0, 120), rand(0, 120));      //0-120深颜色
            //设置需要随机取的值,去掉容易出错的值如0和o
            $data = 'abcdefghigkmnpqrstuvwxy3456789';
            //取出值，字符串截取方法  strlen获取字符串长度
            $fontcontent = substr($data, rand(0, strlen($data)), 1);
            //10>.=连续定义变量
            $captcha_code .= $fontcontent;
            //设置坐标
            $x = ($i * $width / $num) + rand(5, 10);
            $y = rand(5, 10);
            imagestring($image, $fontsize, $x, $y, $fontcontent, $fontcolor);
        }
        //10>存到session
        Illuminate\Support\Facades\Session::put('VerifyCode', $captcha_code);
        //8>增加干扰元素，设置雪花点
        for ($i = 0; $i < 200; $i++) {
            //设置点的颜色，50-200颜色比数字浅，不干扰阅读
            $pointcolor = imagecolorallocate($image, rand(50, 200), rand(50, 200), rand(50, 200));
            //imagesetpixel — 画一个单一像素
            imagesetpixel($image, rand(1, 99), rand(1, 29), $pointcolor);
        }
        //9>增加干扰元素，设置横线
        for ($i = 0; $i < 4; $i++) {
            //设置线的颜色
            $linecolor = imagecolorallocate($image, rand(80, 220), rand(80, 220), rand(80, 220));
            //设置线，两点一线
            imageline($image, rand(1, 99), rand(1, 29), rand(1, 99), rand(1, 29), $linecolor);
        }

        //2>设置头部，image/png
        header('Content-Type: image/png');
        //3>imagepng() 建立png图形函数
        imagepng($image);
        //4>imagedestroy() 结束图形函数 销毁$image
        imagedestroy($image);
    }
}

if (!function_exists('mytrim')) {
    function mytrim($str)
    {
        $username = str_replace(' ', '', $str);
        $username = trim($username);
        return $username;
    }
}


if (!function_exists('is_all_chinese')) {
    /**
     *判断姓名是否全是中文
     * @param $str
     * @return bool
     */
    function is_all_chinese($str)
    {
        //新疆等少数民族可能有·
        if (strpos($str, '·')) {
            //将·去掉，看看剩下的是不是都是中文
            $str = str_replace("·", '', $str);
            if (preg_match('/^[\x7f-\xff]+$/', $str)) {
                return true;//全是中文
            } else {
                return false;//不全是中文
            }
        } else {
            if (preg_match('/^[\x7f-\xff]+$/', $str)) {
                return true;//全是中文
            } else {
                return false;//不全是中文
            }
        }
    }
}
