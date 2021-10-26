
#include <ArduinoOTA.h>
#include <math.h>

#include "transistor.h"

#include "config.h"


namespace transistor {
    double dc = 0;
    double cycletime = 500;

    void setDutyCycle(int percent) {
        if (0 <= percent && percent <= 90) dc = percent;
    }

    int getDutyCycle() {
        return dc;
    }

    void increaseDutyCycle(int percent) {
        if (percent >= 0) dc = min(floor(dc + percent), (double) 90);
    }

    void decreaseDutyCycle(int percent) {
        if (percent >= 0) dc = max(floor(dc - percent), (double) 0); 
    }

    void cycle(unsigned long time) {
        double wait = cycletime * (1 - dc/100) - time;
        delay(max(floor(wait),(double) 0));
        digitalWrite(MOS1PIN, HIGH);
        digitalWrite(MOS2PIN, HIGH);
        delay(ceil(cycletime * (dc / 100)));
        digitalWrite(MOS1PIN, LOW);
        digitalWrite(MOS2PIN, LOW);
    }

}
