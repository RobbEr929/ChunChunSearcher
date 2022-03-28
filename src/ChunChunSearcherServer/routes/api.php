<?php

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| API Routes
|--------------------------------------------------------------------------
|
| Here is where you can register API routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| is assigned the "api" middleware group. Enjoy building your API!
|
*/

Route::middleware('auth:api')->get('/user', function (Request $request) {
    return $request->user();
});
Route::prefix('ccs')->namespace('ChunChunSearcher')->group(function () {
    Route::get('sign','ChunChunSearcherController@Sign');
    Route::get('getconf','ChunChunSearcherController@GetConf');
    Route::get('getinfo','ChunChunSearcherController@GetInfo');
    Route::post('updatetime','ChunChunSearcherController@UpdateTime');
    Route::post('register','ChunChunSearcherController@Register');
    Route::post('writeconf','ChunChunSearcherController@WriteConf');
    Route::post('writeinfo','ChunChunSearcherController@WriteInfo');
});
