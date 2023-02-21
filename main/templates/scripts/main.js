/**
 * @fileoverview
 * Provides the JavaScript interactions for all pages.
 *
 * @author 
 * Jason Su
 */

var _url = "http://192.168.7.2:8082";
// var _url = "http://127.0.0.1:8082";
var rhit = rhit || {};

rhit.fbPlotList = null;

function htmlToElement(html){
	var template = document.createElement("template");
	html = html.trim();
	template.innerHTML = html;
	return template.content.firstChild;
}

rhit.dataPlot = class{
    constructor(name, url, freq, dataLength, ylim, time){
        this.name=name;
        this.url = url;
        this.freq=freq;
        this.dataLength=dataLength;
        this.ylim=ylim;
        this.dps = [];
        this.chart = [];
        this.prevTime = time;
    }

    createChart(){
        this.chart= new CanvasJS.Chart(this.name, {
            exportEnabled: true,
            title :{
                text: "Plot: " + this.name
            },
            axisY: {
                minimum: this.ylim[0],
                maximum: this.ylim[1]
            },
            data: [{
                type: "spline",
                markerSize: 1,
                dataPoints: this.dps 
            }]
        });
    }

    putdata(xVals, yVals){
        //console.log(xVals);
        let maxV = xVals[0];
        let count = 0;
        for(let i = xVals.length-1; i >=0 ; i--){
        //for(let i = 0; i < xVals.length; i++){
            if(xVals[i] > this.prevTime){ // need to be changed
                this.dps.push({
                    x: (xVals[i]-initialTime)*1,
                    y: yVals[i]*1
                });
                if(xVals[i]>maxV){
                    maxV = xVals[i];
                    count++;
                }
            }
            this.prevTime = maxV;
            //console.log("accel: "+yVals[i]+ " | "+ (xVals[i]-initialTime)*1);
            console.log("count: "+count+ " | Length"+ xVals.length);
        }
        //console.log("data put");
        while (this.dps.length > this.dataLength) {
            this.dps.shift();
        }
    }

    refresh(){
        fetch(_url+'/data/'+this.url + '=' + this.freq)
        .then(response => response.json())
        .then(data => {
            let xVals=data.ts;
            let yVals=data.param;
            this.putdata(xVals, yVals);
            this.chart.render();
            console.log(this.name);
        });
    }
}

rhit.plotList = class{
    constructor(){
        this.plotsL = [];
    }
    
    _createPlot(plot){
        return htmlToElement(`<div id=${plot.name} style="height: 370px; max-width: 920px; margin: 0px auto;"></div>`);   
    }

    updateList(){
        console.log("Updating plot list");
        const oldList = document.querySelector('.list-group');
        //const newList = htmlToElement('<div class="list-group"></div>');
        const plotsL = this.plotsL;
        const newPlot = this._createPlot(plotsL[plotsL.length-1]);
        oldList.appendChild(newPlot);
        // oldList.parentElement.appendChild(newList);
		// oldList.removeAttribute("class");
		// oldList.remove();
    }

    add(plot){
        this.plotsL.push(plot);
        this.updateList();
        plot.createChart();
    }

    refresh(){
        //console.log("refreshing data");
        if(this.plotsL==null){
            return;
        }
        //console.log(this.plotsL.length);
        for(let i = 0; i< this.plotsL.length; i++){
            this.plotsL[i].refresh();
        }
        
    }
}

var initialTime = 0;

rhit.runPlot =  function(){
    var dropdownContent = document.querySelector(".dropdown-content");
    var buttons = dropdownContent.getElementsByTagName("a");
     for (var i = 0; i < buttons.length; i++) {
        buttons[i].addEventListener("click", function(event) {
        // Get the HTML content of the button
        var buttonText = event.target.innerHTML;
        var buttonId = event.target.id;
        // Your JavaScript code goes here
        buttonText = buttonText.replace(" ", "_");
        buttonId = buttonId.split("_");
        console.log("Button text: " + buttonText);
        console.log(buttonId);
        let p = new rhit.dataPlot(buttonText, buttonId[0], parseInt(buttonId[1]), parseInt(buttonId[2]), [parseInt(buttonId[3]), parseInt(buttonId[4])], initialTime);
        rhit.fbPlotList.add(p);
        });
    }
    // let p1 = new rhit.dataPlot('accelx', 'accelx', 40, 1000, [-30, 30], initialTime);
    // let p2 = new rhit.dataPlot('accely', 'accelx', 40, 1000, [-30, 30], initialTime);
    // rhit.fbPlotList.add(p1);
    // rhit.fbPlotList.add(p2);
    setInterval(function(){rhit.fbPlotList.refresh()}, 400);
}

rhit.main = function () {
    rhit.fbPlotList = rhit.fbPlotList || new rhit.plotList();
    // Get the dropdown content element
    
    // Add event listeners to the buttons in the dropdown list
    fetch(_url+'/time')
    .then(response => response.json())
    .then(data => {
        initialTime = data.time;
        console.log(initialTime);
        rhit.runPlot();
    });
}

rhit.main();