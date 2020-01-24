<!DOCTYPE html>
<html lang="{{ str_replace('_', '-', app()->getLocale()) }}">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Pompa ciepła - ustawienia</title>

    <!-- Fonts -->
    <link href="https://fonts.googleapis.com/css?family=Nunito:200,600" rel="stylesheet">
    <link href="{{asset('css/app.css')}}" rel="stylesheet">
</head>
<body>
<div class="container">
    <h1 class="header">Monitoring pracy pompy ciepła - ustawienia</h1>
    <a href="{{route('home')}}" class="back-arrow">
        Powrót
    </a>
</div>
<div class="settings-main-container">
    <form action="{{route('settings.save')}}" method="POST">
        @csrf
    <div class="form-container">
        <label class="form-label" for="TEMP_NEEDED">Temperatura wymagana</label>
        <div class="form-control">
            <input type="number" class="form-input" step="0.1" name="TEMP_NEEDED" id="TEMP_NEEDED"
                   value="{{$settings->TEMP_NEEDED}}">
        </div>
    </div>

    <div class="form-container">
        <label class="form-label" for="HISTEREZA">Histereza</label>
        <div class="form-control">
            <input type="number" class="form-input" step="0.1" name="HISTEREZA" id="HISTEREZA"
                   value="{{$settings->HISTEREZA}}">
        </div>
    </div>
    <HR>
    <div style="width: 100%; text-align: center;">
        <h4 style="font-weight: bolder;">!!! ZMIANA PONIŻSZYCH PARAMETRÓW MOŻE WPŁYNĄĆ NA BEZPIECZEŃSTWO PRACY POMPY CIEPŁA !!!</h4>
    </div>
    <div class="form-container">
        <label class="form-label" for="TEMP_MAX_BUFORA">Maksymalna temperatura bufora</label>
        <div class="form-control">
            <input type="number" class="form-input" step="0.1" name="TEMP_MAX_BUFORA" id="TEMP_MAX_BUFORA"
                   value="{{$settings->TEMP_MAX_BUFORA}}">
        </div>
    </div>

    <div class="form-container">
        <label class="form-label" for="TEMP_MAX_IN">Maksymalna temperatura zasilania</label>
        <div class="form-control">
            <input type="number" class="form-input" step="0.1" name="TEMP_MAX_IN" id="TEMP_MAX_IN"
                   value="{{$settings->TEMP_MAX_IN}}">
        </div>
    </div>

    <div class="form-container">
        <label class="form-label" for="TEMP_MAX_OUT">Maksymalna temperatura powrotu</label>
        <div class="form-control">
            <input type="number" class="form-input" step="0.1" name="TEMP_MAX_OUT" id="TEMP_MAX_OUT"
                   value="{{$settings->TEMP_MAX_OUT}}">
        </div>
    </div>

    <div class="form-container">
        <label class="form-label" for="P_MAX_IN">Maksymalne ciśnienie ssania</label>
        <div class="form-control">
            <input type="number" class="form-input" step="0.1" name="P_MAX_IN" id="P_MAX_IN"
                   value="{{$settings->P_MAX_IN}}">
        </div>
    </div>

    <div class="form-container">
        <label class="form-label" for="P_MAX_OUT">Maksymalne ciśnienie tłoczenia</label>
        <div class="form-control">
            <input type="number" class="form-input" step="0.1" name="P_MAX_OUT" id="P_MAX_OUT"
                   value="{{$settings->P_MAX_OUT}}">
        </div>
    </div>
        <div class="form-container">
            <label class="form-label" for="TURBO">Tryb turbo( szybsze ogrzewanie )
            <div class="form-control">
                <input type="radio" class="form-input" name="TURBO"
                       @if($settings->TURBO == 1)
                       checked
                       @endif
                       value="1">
            </div>
            </label>
            <label class="form-label" for="TURBO">Tryb normalny
            <div class="form-control">
                <input type="radio" class="form-input" name="TURBO"
                       @if($settings->TURBO == 0)
                       checked
                       @endif
                       value="0">
            </div>
            </label>
        </div>

        <div class="form-container">
        <input style="background-color: blue; color: white; border: none; padding: 3px 5px 3px 5px; cursor: pointer;" type="submit" value="Zapisz zmiany" onclick="alert('Zmieniono dane!')">
        </div>
    </form>
</div>


</body>

</html>
