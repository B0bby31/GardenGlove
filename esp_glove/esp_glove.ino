/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#include "config.h"
#include "debug.h"

#include "webserver.h"
#include "settings.h"
#include "cli.h"

void setup() {
    debug_init();

    delay(200);

    settings::begin(false);
    cli::begin();
    webserver::begin();

    debug("\n[~~~ Glove v");
    debug(VERSION);
    debugln(" Started! ~~~]");

}

void loop() {
    webserver::update();

    debug_update();
}
