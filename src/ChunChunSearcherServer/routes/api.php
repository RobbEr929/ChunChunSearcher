<?php

use Illuminate\Support\Facades\Route;


Route::prefix('ccs')->namespace('ChunChunSearcher')->group(function () {
    // 个人
    Route::get('sign','ChunChunSearcherController@Sign');
    Route::post('register','ChunChunSearcherController@Register');
    Route::get('getuserinfo','ChunChunSearcherController@GetUserInfo');

    // 配置
    Route::get('getconf','ChunChunSearcherController@GetConf');
    Route::post('writeconf','ChunChunSearcherController@WriteConf');

    // 组织
    Route::post('leaveorganization','ChunChunSearcherController@LeaveOrganization');
    Route::post('applyjoinorganization','ChunChunSearcherController@ApplyJoinOrganization');
    Route::post('joinorganization','ChunChunSearcherController@JoinOrganization');
    Route::post('refuseorganization','ChunChunSearcherController@RefuseOrganization');
    Route::get('getorganizationmembers','ChunChunSearcherController@GetOrganizationMembers');
    Route::post('createorganization','ChunChunSearcherController@CreateOrganization');
    Route::post('dissolveorganization','ChunChunSearcherController@DissolveOrganization');
    Route::get('showappealorganization','ChunChunSearcherController@ShowAppealOrganization');
    Route::post('uporganizationmemberpower','ChunChunSearcherController@UpOrganizationMemberPower');
    Route::post('loworganizationmemberpower','ChunChunSearcherController@LowOrganizationMemberPower');


    // 管理员
    Route::get('showuser','ChunChunSearcherController@ShowUser');
    Route::post('banuser','ChunChunSearcherController@BanUser');
    Route::post('resetuser','ChunChunSearcherController@ResetUser');
    Route::post('appealuser','ChunChunSearcherController@AppealUser');
    Route::get('showorganization','ChunChunSearcherController@ShowOrganization');
    Route::post('banorganization','ChunChunSearcherController@BanOrganization');
    Route::post('resetorganization','ChunChunSearcherController@ResetOrganization');
    Route::post('appealorganization','ChunChunSearcherController@AppealOrganization');
    Route::get('showfile','ChunChunSearcherController@ShowFile');
    Route::post('banfile','ChunChunSearcherController@BanFile');
    Route::post('resetfile','ChunChunSearcherController@ResetFile');
    Route::post('appealfile','ChunChunSearcherController@AppealFile');

    //文件
    Route::get('showuserfile','ChunChunSearcherController@ShowUserFile');
    Route::post('uploaduserfile','ChunChunSearcherController@UpLoadUserFile');
    Route::post('deleteuserfile','ChunChunSearcherController@DeleteUserFile');
    Route::get('showorganizationfile','ChunChunSearcherController@ShowOrganizationFile');
    Route::post('uploadorganizationfile','ChunChunSearcherController@UpLoadOrganizationFile');
    Route::get('downloadfile','ChunChunSearcherController@DownLoadFile');
    Route::post('deleteorganizationfile','ChunChunSearcherController@DeleteOrganizationFile');





});
