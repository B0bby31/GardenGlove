window.addEventListener("load", function (){
    E("reset").onclick = function() {
        if (confirm("Reset all settings to default?")) {
          ws_send("reset", function(msg) {
            load_settings();
          });
          window.location.href="index.html";
        }
    }
    E("modeChangerHeading").innerHTML = "Click on button to change the mode";
    ws_init();
}, false);

function ws_connected() {
    return;
}

//put current temperature value into slider on page load
var backgroundColor = '#eb5c34';

/*slider.value = temperatureSetting;*/


function load_settings() {
    ws_send("settings", function(msg) {
        var lines = msg.split(/\n/);
  
        var temperature = lines[3].split("=")[1];
  
        if (temperature == null);
        else {
            E("temperatureRange").value = temperature;
            E("demo").innerHTML = temperature;
        }
    });
  }

function changeColor(color) {
    document.body.style.background = color;
}

function autoRun() {
    changeColor(backgroundColor);
    E("modeChangerHeading").innerHTML = "Autonomous mode has been selected";
    document.getElementById("selectTemperature").style.display = "none";
    document.getElementById("slideTemperature").style.display = "block";
    document.getElementById("loading").style.display = "flex";
    // Update the current slider value (each time you drag the slider handle) and set background color
    E("slider").oninput = function() {
    E("demo").innerHTML = E("temperatureRange").value;
    document.getElementById("loading").style.display = "flex";
    if(this.value >= 15 && this.value < 18){
        changeColor("#b4eb34");
        backgroundColor = "#b4eb34";
    }
    if(this.value >= 18 && this.value < 20){
        changeColor("#eb9f34");
        backgroundColor = "#eb9f34";
    }
    if(this.value >= 20 && this.value < 23){
        changeColor("#eb5c34");
        backgroundColor = "#eb5c34";
    }
    if(this.value >= 23 && this.value <= 25){
        changeColor("#eb3434");
        backgroundColor = "#eb3434";
    }
    //send Temperature based on slider input
    var temperature = E("temperatureRange").value;
    if (temperature) {
      if (temperature >= 15 && temperature <= 35) {
        ws_send("set targetTemp \"" + temperature + "\"", function(msg) {
        });
      } else {
        alert("ERROR: Invalid temperature");
      }
    }
    
    }
    load_settings();
}         

function manualRun() {
    changeColor('#b4eb34');
    E("modeChangerHeading").innerHTML = "Manual mode has been selected";
    document.getElementById("selectTemperature").style.display = "block";
    document.getElementById("loading").style.display = "none";
    document.getElementById("slideTemperature").style.display = "none";
}         


