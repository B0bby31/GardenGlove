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
#include "battery.h"
#include "test.h"

bool event1 = false;
bool event2 = false;
bool autoM = true;
unsigned long startCycle;
int currentDC;
int currentStep = 10;
unsigned long endCycle;
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
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(RED, OUTPUT);
    attachInterrupt(BUTTON1PIN, press1, RISING);
    attachInterrupt(BUTTON2PIN, press2, RISING);
    digitalWrite(GREEN, HIGH); // For Anton
    delay(2000);
    digitalWrite(GREEN, LOW);
    settings::begin(false);
    cli::begin();
    webserver::begin();


    debug("\n[~~~ Glove v");
    debug(VERSION);
    debugln(" Started! ~~~]");
}

void automatic(unsigned long timeOne) {
  if(!first) {
    currentDC = 50;
    transistor::setDutyCycle(50);
  }
  first = true;
  if(autoM) {
    startCycle = millis();
    autoM = false;
  }
  endCycle = millis();
  if (endCycle - startCycle >= 4000) {
    autoM = true;
    if (settings::getTemperature() > sensor::readingSensorTwo()) {
      transistor::increaseDutyCycle(currentStep);
    } else if (settings::getTemperature() < sensor::readingSensorTwo()) {
      transistor::decreaseDutyCycle(currentStep);
    } 
    if ((settings::getTemperature() - sensor::readingSensorTwo()) > 4 || (settings::getTemperature() - sensor::readingSensorTwo()) < -4 );
    else currentStep = currentStep / 2;
  } else {
      unsigned long CurrentTime = millis();
      transistor::cycle(CurrentTime - timeOne);
  }
}

void manual(unsigned long timeOne) {
  if(first) {
      transistor::setDutyCycle(0);
      autoM = true;
      currentStep = 10;
  }
  first = false;
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
  transistor::cycle(CurrentTime - timeOne);
}


void loop() {
  unsigned long StartTime = millis();
  debug_update();
  webserver::update();
  if (test::getMode()) {
    automatic(StartTime);
  } else {
    manual(StartTime);
  }
}
