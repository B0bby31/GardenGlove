/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#include <Arduino.h> // String

namespace settings {
    void begin(bool mode);
    void load();
    void end();

    void reset();

    String toString();

    const char* getSSID();
    const char* getPassword();
    const char* getChannel();

    int getChannelNum();

    void set(const char* name, const char* value);

    void setSSID(const char* ssid);
    void setPassword(const char* password);
    void setChannel(const char* channel);
}
