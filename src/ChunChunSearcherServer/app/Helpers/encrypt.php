<?php
/**
 * Created by PhpStorm.
 * User: myxy9
 * Date: 2020/4/28
 * Time: 13:15
 */

if (!function_exists('privateDecrypt')) {
    /**
     * //解密
     * @param string $encryptString
     * @return string
     */
    function privateDecrypt($encryptString = '')
    {
        $privateKey = storage_path('key/exam.key');
        $decrypted = '';
        foreach (explode("__&_&__", base64_decode($encryptString)) as $chunk) {
            openssl_private_decrypt($chunk, $decryptData, file_get_contents($privateKey));
            $decrypted .= $decryptData;
        }
        return $decrypted;
    }
}

if (!function_exists('publicEncrypt')) {
    /**
     * //加密
     * @param string $data
     * @return string
     */
    function publicEncrypt($data = '')
    {
        $publicKey = storage_path('key/exam_pub.key');
        $encrypt_data = '';
        foreach (str_split(json_encode($data), 117) as $chunk) {
            openssl_public_encrypt($chunk, $encryptData, file_get_contents($publicKey));
            $encrypt_data .= base64_encode($encryptData) . "__&_&__";
        }
        return $encrypt_data;
    }

}