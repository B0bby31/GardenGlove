
#include <ArduinoOTA.h>
#include <math.h>

#include "battery.h"

#include "config.h"


namespace battery {
    double currentReadingOne = (analogReadMilliVolts(CELLONE) * 2) / 1000;
    double currentReadingTwo = (analogReadMilliVolts(CELLTWO) * 3.2) / 1000 - currentReadingOne;
    double readingCellOne() {
        double average = 0;
        average += (analogReadMilliVolts(CELLONE) * 2) / 1000;
        delay(1);
        average += (analogReadMilliVolts(CELLONE) * 2) / 1000;
        delay(1);
        average += (analogReadMilliVolts(CELLONE) * 2) / 1000;
        delay(1);
        currentReadingOne = average / 3;
        return currentReadingOne;
    }

    double readingCellTwo() {
        double average = 0;
        average += (analogReadMilliVolts(CELLTWO) * 3.2) / 1000;
        delay(1);
        average += (analogReadMilliVolts(CELLTWO) * 3.2) / 1000;
        delay(1);
        average += (analogReadMilliVolts(CELLTWO) * 3.2) / 1000;
        delay(1);
        currentReadingTwo = average / 3;
        return currentReadingTwo;
    }

    int percentageCellOne() {
        double percent = ((readingCellOne() - MINVOLTAGE) / (MAXVOLTAGE - MINVOLTAGE)) * 100;
        return floor(percent);
    }
    int percentageCellTwo() {
        double percent = ((readingCellTwo() - MINVOLTAGE) / (MAXVOLTAGE - MINVOLTAGE)) * 100;
        return min(floor(percent),(double) 100);
    }
    String toStringOne() {
      String s;

      s += "Cell1=";
      s += percentageCellOne();
      s += "\n";
      s += "Cell2=";
      s += percentageCellTwo();
      s += "\n";

      return s;
    }
}
