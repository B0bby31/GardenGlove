/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#include "config.h"
#include "debug.h"

#include "webserver.h"
#include "settings.h"
#include "cli.h"

bool event1 = false;
bool event2 = false;

void IRAM_ATTR press1() {
    event1 = true;
}

void IRAM_ATTR press2() {
    event2 = true;
}

void setup() {
    debug_init();

    delay(200);
    pinMode(BUTTON1PIN, INPUT_PULLUP);
    pinMode(BUTTON2PIN, INPUT_PULLUP);
    attachInterrupt(BUTTON1PIN, press1, RISING);
    attachInterrupt(BUTTON2PIN, press2, RISING);
    settings::begin(false);
    if(settings::getSSID(true) && settings::getPassword(true)) {
      settings::end();
      settings::begin(true);
    } else {
      cli::begin();
      webserver::begin();
    }

    debug("\n[~~~ Glove v");
    debug(VERSION);
    debugln(" Started! ~~~]");

}

void loop() {
    webserver::update();
    if(event1 && event2) {
      debugln(" Success12");
      delay(100);
      event1 = false;
      event2 = false;
    } else if (event1) {
      debugln(" Success1");
      delay(100);
      event1 = false;
    } else if (event2) {
      debugln(" Success2");
      delay(100);
      event2 = false;     
    }
    debug_update();
}
