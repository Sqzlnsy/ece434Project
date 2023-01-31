var _url = "http://172.19.98.231:8081/";

window.onload = function () {

    var dps = [];
    var chart = new CanvasJS.Chart("chartContainer", {
        exportEnabled: true,
        title :{
            text: "Dynamic Spline Chart"
        },
        axisY: {
            includeZero: false
        },
        data: [{
            type: "spline",
            markerSize: 0,
            dataPoints: dps 
        }]
    });
    
    var xVal = 0;
    var yVal = 0;
    var updateInterval = 100;
    var dataLength = 50; // number of dataPoints visible at any point

    var getData = function(){
        fetch(_url+'/data')
        .then(response => response.json())
        .then(data => {
            xVal=data.ts;
            yVal=data.accelx;
            console.log(data);
        });
    }
    
    var updateChart = function () {
        // count is number of times loop runs to generate random dataPoints.
        dps.push({
            x: xVal,
            y: yVal
        });
        if (dps.length > dataLength) {
            dps.shift();
        }
        chart.render();
    };
    
    updateChart(dataLength); 
    setInterval(function(){getData(); updateChart() }, updateInterval); 
    }