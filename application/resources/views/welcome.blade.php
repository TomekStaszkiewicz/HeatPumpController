<!DOCTYPE html>
<html lang="{{ str_replace('_', '-', app()->getLocale()) }}">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Pompa ciepła</title>

    <!-- Fonts -->
    <link href="https://fonts.googleapis.com/css?family=Nunito:200,600" rel="stylesheet">
    <link href="{{asset('css/app.css')}}" rel="stylesheet">
</head>
<body>
<div class="container">
    <h1 class="header">Monitoring pracy pompy ciepła</h1>
</div>
<a href="{{route('settings')}}" class="back-arrow">Ustawienia</a>
<div class="charts-container">
    Dane z tygodnia
    <div class="chart-card">
        <canvas id="tools"></canvas>
    </div>
</div>
<div class="charts-container">
    Dane z dnia
    <div class="chart-card">
        <canvas id="tools-day"></canvas>
    </div>
</div>
<div class="charts-container">
    Dane z godziny
    <div class="chart-card">
        <canvas id="hour"></canvas>
    </div>
</div>
<div class="charts-container">
    Dane z dnia
    <div class="chart-card">
        <canvas id="day"></canvas>
    </div>
</div>
<div style="clear: both"></div>
<div class="charts-container">
    Dane z tygodnia
    <div class="chart-card">
        <canvas id="week"></canvas>
    </div>
</div>

<div class="charts-container">
    Dane z miesiąca
    <div class="chart-card">
        <canvas id="month"></canvas>
    </div>
</div>

<div style="clear: both"></div>

</body>
<script src="{{asset('js/app.js')}}" ></script>
@if($deficite > 20 && $turbo == 0)
<script>
    alert('Bardzo niska temepratura bufora. Zalecane wlaczenie trybu turbo');
</script>
@endif
</html>
