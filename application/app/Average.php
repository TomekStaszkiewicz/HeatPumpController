<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Average extends Model
{

    protected $fillable = [
        'id',
        'temp_ext',
        'temp_in',
        'temp_out',
        'p_in',
        'p_out',
        'temp_bufora',
        'sprezarka',
        'pompa_dol',
        'pompa_gora',
    ];





}
