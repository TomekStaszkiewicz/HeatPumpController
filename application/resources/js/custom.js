import 'axios';
require('chart.js');


window.onload =  function(){
    drawCharts();
};

function createChart( apiData, el )
{
    let chart = new Chart(el, {
        type: 'line',
        data: {
            labels: apiData.labels,
            datasets: apiData.data,
        }
    })
}

function getCanvas()
{
    let day = document.getElementById('day').getContext('2d');
    let week = document.getElementById('week').getContext('2d');
    let month = document.getElementById('month').getContext('2d');
   let hour = document.getElementById('hour').getContext('2d');
   let tools = document.getElementById('tools').getContext('2d');
   let toolsDay = document.getElementById('tools-day').getContext('2d');
    return {
        day: day,
        week: week,
        month: month,
       hour: hour,
       tools: tools,
       toolsDay: toolsDay
    };
}

async function drawCharts()
{
    let canvs = getCanvas();
    let apiData = {};
    axios.get('/api/getdata')
        .then( res => {
            apiData = res.data;
            console.log( apiData );
        })
        .then( () => {
            createChart( apiData.day, canvs.day );
            createChart( apiData.week, canvs.week );
            createChart( apiData.month, canvs.month );
           createChart( apiData.hour, canvs.hour );
           createChart( apiData.tools, canvs.tools );
           createChart( apiData.toolsDay, canvs.toolsDay );
        })
        .catch( (err) => console.error(`Problem z pobieraniem danych: ${err}`))

}