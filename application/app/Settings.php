<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Settings extends Model
{
    protected $fillable = [
        'temp_needed',
        'temp_max_in',
        'temp_max_out',
        'p_max_in',
        'p_max_out',
        'histereza',
        'temp_max_bufora',
        'turbo',
    ];
    public $timestamps = false;
}
