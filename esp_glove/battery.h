#pragma once

#include <Arduino.h> // String

namespace battery {
    double readingCellOne();
    double readingCellTwo();

    int percentageCellOne();
    int percentageCellTwo();
}