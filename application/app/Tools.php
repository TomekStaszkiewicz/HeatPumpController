<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Tools extends Model
{

    protected $fillable = [
       'sprezarka',
		'pompa_dol',
		'pompa_gora',
		'czas_pompa',
		'czas_sprezarka',
    ];
}
