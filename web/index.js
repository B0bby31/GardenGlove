/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */


// ========== Global Variables ========== //



function ws_connected() {
  load_settings();
}



function load_settings() {
  ws_send("settings", function(msg) {
      var lines = msg.split(/\n/);

      var ssid = lines[0].split("=")[1];
      var password = lines[1].split("=")[1];

      if (ssid == null);
      else document.getElementById('ssidInput').value = ssid;
      if (password == null);
      else document.getElementById('passwordInput').value = password;

  });
}


window.addEventListener("load", function (){
  E("submit").onclick = function () {
      var newssid = document.getElementById('ssidInput').value;
      var newpassword = document.getElementById('passwordInput').value;
      console.log(newssid);
      console.log(newpassword);
      if (newssid) {
        if (newssid.length >= 1 && newssid.length <= 32) {
          ws_send("set ssid \"" + newssid + "\"", function(msg) {
            load_settings();
          });
        } else {
          alert("ERROR: Invalid length");
          return;
        }
      }
      if (newpassword) {
        if (newpassword.length >= 8 && newpassword.length <= 64) {
          ws_send("set password \"" + newpassword + "\"", function(msg) {
            load_settings();
          });
        } else {
          alert("ERROR: Invalid length");
          return;
      }
    }
    window.location.href = "mainPage.html";
  }
  ws_init();
}, false);