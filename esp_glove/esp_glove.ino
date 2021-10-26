/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#include "config.h"
#include "debug.h"

#include "webserver.h"
#include "settings.h"
#include "cli.h"
#include "transistor.h"
#include "sensor.h"

bool event1 = false;
bool event2 = false;
bool mode1 = false; // what mode is the esp currently in
bool first = true; // is it the first mode switch

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
    pinMode(DEBUG_LED, OUTPUT);
    pinMode(MOS1PIN, OUTPUT);
    pinMode(MOS2PIN, OUTPUT);
    attachInterrupt(BUTTON1PIN, press1, RISING);
    attachInterrupt(BUTTON2PIN, press2, RISING);
    settings::begin(true);
    cli::begin();


    debug("\n[~~~ Glove v");
    debug(VERSION);
    debugln(" Started! ~~~]");

}

void automatic() {
  if (!first) webserver::end();
  first = true;
}

void manual() {
  if (first) webserver::begin();
  first = false;
  unsigned long StartTime = millis();
  webserver::update();
  if (event1) {
    debugln(sensor::readingSensorOne());
    transistor::increaseDutyCycle(10);
    digitalWrite(DEBUG_LED,HIGH);
    delay(100);
    digitalWrite(DEBUG_LED,LOW);
    event1 = false;
  } else if (event2) {
    transistor::decreaseDutyCycle(10);
    delay(100);
    event2 = false;     
  }
  unsigned long CurrentTime = millis();
  transistor::cycle(CurrentTime - StartTime);
}


void loop() {
  if (mode1) {
    automatic();
  } else {
    manual();
  }
  debug_update();
}
