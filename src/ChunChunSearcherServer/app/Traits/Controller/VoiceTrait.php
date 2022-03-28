<?php

namespace App\Traits\Controller;

use Illuminate\Support\Str;

trait VoiceTrait
{
    // 只允许以下后缀名的图片文件上传
    protected $allowed_ext = ["mp3"];

    /**
     * 上传图片
     *
     * @param [type] $file, 待上传的音频
     * @param [type] $folder, 指定上传的文件夹
     * @param [type] $file_prefix, 指定上传文件名的前缀
     * @return array
     */
    public function save($file, $folder)
    {
        // 构建存储的文件夹规则，值如：uploads/voice/listening/201709/21/
        // 文件夹切割能让查找效率更高。
        $folder_name = "uploads/$folder/" . date("Ym/d", time());

        // 文件具体存储的物理路径，`public_path()` 获取的是 `public` 文件夹的物理路径。
        // 值如：/home/vagrant/Code/exam/public/uploads/voice/listening/201709/21/
        $upload_path = public_path() . '/' . $folder_name;

        // 获取文件的后缀名，因图片从剪贴板里黏贴时后缀名为空，所以此处确保后缀一直存在
        $extension = strtolower($file->getClientOriginalExtension()) ?: 'mp3';

        // 拼接文件名
        // 值如：1493521050_7BVc9v9ujP.mp3
        $filename = time() . '_' . Str::random(10) . '.' . $extension;

        // 将图片移动到我们的目标存储路径中
        $file->move($upload_path, $filename);

        return [
            'path' => config('app.url') . "/$folder_name/$filename"
        ];
    }
}
