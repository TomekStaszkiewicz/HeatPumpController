<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', 'MainController@index')->name('home');
Route::get('settings', 'MainController@settings')->name('settings');

Route::get('/api/getdata', 'MainController@getData');
Route::post('/api/savesettings', 'MainController@saveSettings')->name('settings.save');