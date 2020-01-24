<?php

namespace App\Console;

use Illuminate\Console\Scheduling\Schedule;
use Illuminate\Foundation\Console\Kernel as ConsoleKernel;
use App\Data;
use App\Tools;
use App\Average;

class Kernel extends ConsoleKernel
{
    /**
     * The Artisan commands provided by your application.
     *
     * @var array
     */
    protected $commands = [
        //
    ];

    /**
     * Define the application's command schedule.
     *
     * @param  \Illuminate\Console\Scheduling\Schedule  $schedule
     * @return void
     */
    protected function schedule(Schedule $schedule)
    {
        // $schedule->command('inspire')
        //          ->hourly();
        $schedule->call( function(){

            $data = Data::latest()->take(720);
            $tools = Tools::latest()->take(720);
            $temp_ext = 0;
            $temp_in = 0;
            $temp_out = 0;
            $p_in = 0;
            $p_out = 0;
            $temp_bufora = 0;
            $sprezarka = 0;
            $pompa_dol = 0;
            $pompa_gora = 0;

        for( $i = 0; $i < 720; $i++)
        {
            $temp_ext += $data[$i]->temp_ext;
            $temp_in += $data[$i]->temp_in;
            $temp_out += $data[$i]->temp_out;
            $p_in +=  $data[$i]->p_in;
            $p_out +=  $data[$i]->p_out;
            $temp_bufora +=  $data[$i]->temp_bufora;
            if($tools[i]->sprezarka)$sprezarka = 1;
            if($tools[i]->pompa_dol)$pompa_dol = 1;
            if($tools[i]->pompa_gora)$pompa_gora = 1;
        }
            $temp_ext /= 720;
            $temp_in /= 720;
            $temp_out /= 720;
            $p_in /= 720;
            $p_out /= 720;
            $temp_bufora /= 720;

            Average::create([
                'temp_ext' => $temp_ext,
                'temp_in' => $temp_in,
                'temp_out' => $temp_out,
                'p_in' => $p_in,
                'p_out' => $p_out,
                'temp_bufora' => $temp_bufora,
                'sprezarka' => $sprezarka,
                'pompa_dol' => $pompa_dol,
                'pompa_gora' => $pompa_gora
            ]);

        })->hourly();
    }

    /**
     * Register the commands for the application.
     *
     * @return void
     */
    protected function commands()
    {
        $this->load(__DIR__.'/Commands');

        require base_path('routes/console.php');
    }
}
