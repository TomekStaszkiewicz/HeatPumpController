<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Data extends Model
{
    protected $fillable = [
        'temp_ext',
		'temp_in',
		'temp_out',
		'p_in',
		'p_out',
		'temp_bufora',
        'timestamp'
        ];
}
