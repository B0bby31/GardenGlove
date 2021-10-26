#include <ArduinoOTA.h>
#include <math.h>

#include "sensor.h"

#include "config.h"


namespace sensor {
    double currentReadingOne = analogReadMilliVolts(TEMP1PIN) / 10;
    double currentReadingTwo = analogReadMilliVolts(TEMP2PIN)/ 10;
    double readingSensorOne() {
        double average = 0;
        average += analogReadMilliVolts(TEMP1PIN)/ 10;
        delay(1);
        average += analogReadMilliVolts(TEMP1PIN)/ 10;
        delay(1);
        average += analogReadMilliVolts(TEMP1PIN)/ 10;
        delay(1);
        currentReadingOne = average / 3;
        return round(currentReadingOne);
    }

    double readingSensorTwo() {
        double average = 0;
        average += analogReadMilliVolts(TEMP2PIN)/ 10;
        delay(1);
        average += analogReadMilliVolts(TEMP2PIN)/ 10;
        delay(1);
        average += analogReadMilliVolts(TEMP2PIN)/ 10;
        delay(1);
        currentReadingTwo = average / 3 - currentReadingOne;
        return round(currentReadingTwo);
    }
}