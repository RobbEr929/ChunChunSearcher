<?php

namespace App\Traits\Controller;


use Intervention\Image\Facades\Image;

trait ImageTrait
{

    /**
     * 图片处理
     * @param $file 文件对象
     * @param $max_width 最大宽度
     * @param int $quality 压缩后质量
     * @return string 上传到gridFS 后的文件id
     */
    public function compressImg($file, $savepath, $max_width, $quality = 85)
    {
        $img = Image::make($file);
        $width = $img->width();
        if ($width > $max_width) {
            // 宽度为900,高度自动调整，不会变形
            $img->resize($max_width, null, function ($constraint) {
                $constraint->aspectRatio();
            })->save($savepath, $quality);
        } else {
            $img->save($savepath, $quality);
        }

        return $img;
    }

    public function compressAvatar($file, $savepath, $max_width, $quality = 85)
    {
        $img = Image::make($file);
        $width = $img->width();
        if ($width > $max_width) {
            // 宽高固定
            $img->resize($max_width, $max_width, function ($constraint) {
                $constraint->aspectRatio();
            })->save($savepath, $quality);
        } else {
            $img->save($savepath, $quality);
        }
        return $img;
    }

    public function compressPoster($file, $savepath, $max_width = 700, $quality = 60)
    {
        $img = Image::make($file);
        $width = $img->width();
        if ($width > $max_width) {
            // 宽高固定
            $img->resize($max_width, $max_width, function ($constraint) {
                $constraint->aspectRatio();
            })->save($savepath, $quality);
        } else {
            $img->save($savepath, $quality);
        }
        return $img;
    }

}
