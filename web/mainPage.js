window.addEventListener("load", function (){
    ws_init();
}, false);

var ssidSetting;
var passwordSetting;
function submitSettings () {
    var newssid = document.getElementById('ssidInput').value;
    var newpassword = document.getElementById('passwordInput').value;
    
    load_settings();
    if (newssid.length != 0 && newpassword.length != 0) {
        window.location.href = "mainPage.html";
    } else {
        if (newssid) {
            if (newssid.length >= 1 && newssid.length <= 32) {
                ws_send("set ssid \"" + newssid + "\"", function(msg) {
                    load_settings();
                });
            } else {
                alert("ERROR: Invalid length");
            }
        }
        if (newpassword) {
            if (newpassword.length >= 8 && newpassword.length <= 64) {
                ws_send("set password \"" + newpassword + "\"", function(msg) {
                    load_settings();
                });
            } else {
                alert("ERROR: Invalid length");
            }
        }
        window.location.href = "mainPage.html";
    }
    
}

//put current temperature value into slider on page load
var slider = document.getElementById("temperatureRange");
var output = document.getElementById("demo");
var backgroundColor = '#eb5c34';

slider.value = temperatureSetting;

output.innerHTML = slider.value; // Display the default slider value

// Update the current slider value (each time you drag the slider handle) and set background color
slider.oninput = function() {
    output.innerHTML = this.value;
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
    var temperature = slider.value;
    if (temperature) {
      if (temperature >= 15 && temperature <= 35) {
        ws_send("set temperature \"" + temperature + "\"", function(msg) {
        });
      } else {
        alert("ERROR: Invalid temperature");
      }
    }
    
}

var el_down = document.getElementById("modeChangerHeading");
var str = "Click on button to change the mode";
el_up.innerHTML = str;

function changeColor(color) {
    document.body.style.background = color;
}

function autoRun() {
    changeColor(backgroundColor);
    el_down.innerHTML = "Autonomous mode has been selected";
    document.getElementById("selectTemperature").style.display = "none";
    document.getElementById("slideTemperature").style.display = "block";
    document.getElementById("loading").style.display = "flex";
}         

function manualRun() {
    changeColor('#b4eb34');
    el_down.innerHTML = "Manual mode has been selected";
    document.getElementById("selectTemperature").style.display = "block";
    document.getElementById("loading").style.display = "none";
    document.getElementById("slideTemperature").style.display = "none";
}         

document.getElementById("reset").onclick = function() {
    if (confirm("Reset all settings to default?")) {
      ws_send("reset", function(msg) {
        load_settings();
      });
    }
};

function load_settings() {
    ws_send("settings", function(msg) {
        var lines = msg.split(/\n/);

        ssidSetting = lines[0].split("=")[1];
        passwordSetting = lines[1].split("=")[1];
        //put it on the slider
        var temperatureSetting = lines[3].split("=")[1];

        document.getElementById('ssidInput').value = ssidSetting;
        document.getElementById('passwordInput').value = passwordSetting;
        document.getElementById("temperatureRange").value = temperatureSetting;
    });
}
