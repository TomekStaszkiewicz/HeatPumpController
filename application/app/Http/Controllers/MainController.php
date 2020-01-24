<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Data;
use App\Settings;
use App\Tools;
use stdClass;
use App\Average;

class MainController extends Controller
{
    public function index()
    {
        $data = Data::orderBy('id', 'desc')->first();
        $settings = Settings::orderBy('id', 'desc')->first();

        $deficite = $settings->TEMP_NEEDED - $data->TEMP_BUFORA;
        $turbo = $settings->TURBO;
//        dd($data, $settings);
        return view('welcome', compact('deficite', 'turbo'));
    }
//zwraca procent czasu przez jaki pracowala sprezarka w danym interwale
    public function calculateTools( $time, $interval, $array )
    {
        $obj1 = new stdClass();
        $obj2 = new stdClass();
        $obj3 = new stdClass();

        $obj1->label = "Praca sprezarki";
        $obj2->label = "Praca pomp obiegowych";

        $obj1->backgroundColor = ["rgba( 135, 64, 52, 0.2)"];
        $obj2->backgroundColor = ["rgba( 235, 214, 52, 0.2)"];

        $obj1->borderColor = ["rgba( 135, 64, 52, 1)"];
        $obj2->borderColor = ["rgba( 235, 214, 52, 1)"];

        $obj1->data = [];
        $obj2->data = [];

        $t1 = 0;
        $t2 = 0;

        if( count($array) > $interval) {
            for ($i = 1; $i <= $time; $i++) {
                $t1 += $array[$i - 1]['SPREZARKA'] ?? 0;
                $t2 += $array[$i - 1]['POMPY'] ?? 0;
                if( $i%$interval === 0 )
                {
                    $obj1->data[] = $t1 / 360;//to get hours
                    $obj2->data[] = $t2 / 360;
                    $t1 = 0;
                    $t2 = 0;
                }
                }
            }
        else{
            for ($i = 1; $i <= count($array); $i++) {
                $t1 += $array[$i - 1]['SPREZARKA'] ?? 0;
                $t2 += $array[$i - 1]['POMPY'] ?? 0;
            }
            $obj1->data[] = $t1/360;
            $obj2->data[] = $t2/360;
        }

        return  [$obj1, $obj2];
    }

    public function calculateAverageData( $time, $interval, $array )
    {

        $obj1 = new stdClass();
        $obj2 = new stdClass();
        $obj3 = new stdClass();
//        $obj4 = new stdClass();
//        $obj5 = new stdClass();
        $obj6 = new stdClass();

        $obj1->label = "Temperatura dolnego zrodla";
        $obj2->label = "Temperatura zasilania";
        $obj3->label = "Temperatura powrotu";
//        $obj4->label = "Cisnienie zasilania";
//        $obj5->label = "Cisnienie powrotu";
        $obj6->label = "Temperatura bufora";

        $obj1->backgroundColor = ["rgba( 135, 64, 52, 0.2)"];
        $obj2->backgroundColor = ["rgba( 235, 214, 52, 0.2)"];
        $obj3->backgroundColor = ["rgba( 101, 235, 52, 0.2)"];
//        $obj4->backgroundColor = ["rgba( 52, 147, 235, 0.2)"];
//        $obj5->backgroundColor = ["rgba( 223, 52, 235, 0.2)"];
        $obj6->backgroundColor = ["rgba( 235, 52, 95, 0.2)"];

        $obj1->borderColor = ["rgba( 135, 64, 52, 1)"];
        $obj2->borderColor = ["rgba( 235, 214, 52, 1)"];
        $obj3->borderColor = ["rgba( 101, 235, 52, 1)"];
//        $obj4->borderColor = ["rgba( 52, 147, 235, 1)"];
//        $obj5->borderColor = ["rgba( 223, 52, 235, 1)"];
        $obj6->borderColor = ["rgba( 235, 52, 95, 1)"];

        $obj1->data = [];
        $obj2->data = [];
        $obj3->data = [];
//        $obj4->data = [];
//        $obj5->data = [];
        $obj6->data = [];

        $t1 = 0;
        $t2 = 0;
        $t3 = 0;
//        $t4 = 0;
//        $t5 = 0;
        $t6 = 0;

if( count($array) > $interval) {
    for ($i = 1; $i <= $time; $i++) {
        $t1 += $array[$i - 1]['TEMP_EXT'] ?? 0;
        $t2 += $array[$i - 1]['TEMP_IN'] ?? 0;
        $t3 += $array[$i - 1]['TEMP_OUT'] ?? 0;
//        $t4 += $array[$i - 1]['P_IN'] ?? 0;
//        $t5 += $array[$i - 1]['P_OUT'] ?? 0;
        $t6 += $array[$i - 1]['TEMP_BUFORA'] ?? 0;

        if ($i % $interval === 0) {
            $t1 /= $interval;
            $t2 /= $interval;
            $t3 /= $interval;
//            $t4 /= $interval;
//            $t5 /= $interval;
            $t6 /= $interval;
            $obj1->data[] = $t1;
            $obj2->data[] = $t2;
            $obj3->data[] = $t3;
//            $obj4->data[] = $t4;
//            $obj5->data[] = $t5;
            $obj6->data[] = $t6;

            $t1 = 0;
            $t2 = 0;
            $t3 = 0;
//            $t4 = 0;
//            $t5 = 0;
            $t6 = 0;

        }
    }
}
else{
    for ($i = 1; $i <= count($array); $i++) {
        $t1 += $array[$i - 1]['TEMP_EXT'] ?? 0;
        $t2 += $array[$i - 1]['TEMP_IN'] ?? 0;
        $t3 += $array[$i - 1]['TEMP_OUT'] ?? 0;
        $t6 += $array[$i - 1]['TEMP_BUFORA'] ?? 0;
    }
    $obj1->data[] = $t1/count($array);
    $obj2->data[] = $t2/count($array);
    $obj3->data[] = $t3/count($array);
    $obj6->data[] = $t6/count($array);
}

        return  [$obj1, $obj2, $obj3, /*$obj4, $obj5,*/ $obj6];
    }

    public function getData()
    {
        $tmp_hour = [];
        $tmp_month = [];
        $tmp_week = [];
        $tmp_day = [];
        $today = date('m/d/Y');
        $base_m = date('m') . '/15/' . date('Y');
        for ($i = 59; $i >= 0; $i--) {
            $tmp_hour[] = date('i', strtotime( " -" . $i . " Minutes"));
        }
        for ($i = 30; $i >= 0; $i--) {
            $tmp_month[] = date('D', strtotime($today . " -" . $i . " Day"));

            $this_day_full_date = (date('Y-m-d', strtotime($today . " -" . $i . " Day"))) . " %:%:%";
        }

        for ($i = 6; $i >= 0; $i--) {
            $tmp_week[] = date('D', strtotime($today . " -" . $i . " Day"));

            $this_day_full_date = (date('Y-m-d', strtotime($today . " -" . $i . " Day"))) . " %:%:%";
        }

        for ($i = 23; $i >= 0; $i--) {
            $tmp_day[] = date('H', strtotime(" -" . $i . " Hours"));

        }
        ////////////////////////////

        $allAverages = Data::latest()->take(259200)->get()->toArray();
        $allTools = Tools::latest()->take(259200)->get()->toArray();

         $obj = new stdClass();
         $hour = new stdClass();
        $day = new stdClass();
        $week = new stdClass();
        $month = new stdClass();
        $tools = new stdClass();
        $toolsDay = new stdClass();

        $hour->labels = $tmp_hour;
        $day->labels = $tmp_day;
        $week->labels = $tmp_week;
        $month->labels = $tmp_month;
        //pompy i sprezarka na przestrzeni tygodnia
        $tools->labels = $tmp_week;
        $toolsDay->labels = $tmp_day;
        //$year->labels = $tmp_year;

        $hour->data = $this->calculateAverageData(  360, 6, $allAverages);
        $day->data = $this->calculateAverageData(  8640, 360, $allAverages);
        $week->data = $this->calculateAverageData( 60480,8640,  $allAverages);
        $month->data = $this->calculateAverageData(  259200, 8640, $allAverages);
        //$year->data = $this->calculateAverageData(  8760, 720, $allAverages);
        $tools->data = $this->calculateTools(60480, 8640, $allTools);
        $toolsDay->data = $this->calculateTools(8640, 360, $allTools);


        $obj->hour = $hour;
        $obj->day = $day;
        $obj->week = $week;
        $obj->month = $month;
      //  $obj->year = $year;
        $obj->tools = $tools;
        $obj->toolsDay = $toolsDay;

        return json_encode($obj);
    }

    public function settings()
    {
        $settings = Settings::orderBy('id', 'desc')->first();
        return view('settings', compact('settings'));
    }

    public function saveSettings( Request $request )
    {
    $data = $request->all();
    $s = new Settings();
        $s->temp_needed = $data['TEMP_NEEDED'];
        $s->temp_max_in = $data['TEMP_MAX_IN'];
        $s->temp_max_out = $data['TEMP_MAX_OUT'];
        $s->p_max_in = $data['P_MAX_IN'];
        $s->p_max_out = $data['P_MAX_OUT'];
        $s->histereza = $data['HISTEREZA'];
        $s->temp_max_bufora = $data['TEMP_MAX_BUFORA'];
        $s->turbo = $data['TURBO'];

        $s->save();
    return redirect()->back();
    }

}
