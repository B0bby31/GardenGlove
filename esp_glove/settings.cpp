/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */
 
#include <Preferences.h>
#include "settings.h"

#include "debug.h"
#include "config.h"

Preferences preferences;

namespace settings {
    // ===== PRIVATE ===== //
    String ssid_ap;
    String password_ap;
    String channel;
    String ssid_sta;
    String password_sta;
    
    // ===== PUBLIC ====== //
    void begin(bool mode) {
        preferences.begin("Settings", mode);
        load();
    }

    void load() {
      ssid_ap = preferences.getString("SSID_AP", WIFI_SSID); 
      password_ap = preferences.getString("Password_AP", WIFI_PASSWORD);
      ssid_sta = preferences.getString("SSID_STA", NETWORK_SSID); 
      password_sta = preferences.getString("Password_STA", NETWORK_PASSWORD);
      channel = preferences.getString("Channel", WIFI_CHANNEL);
    }

    void end() {
      preferences.end();
    }

    // resets settings to default
    void reset() {
        debugln("Resetting Settings");
        setSSID(WIFI_SSID);
        setPassword(WIFI_PASSWORD);
        setChannel(WIFI_CHANNEL);
    }

    void save() {
        debugln("Saving Settings");


        preferences.putString("SSID_STA", ssid_sta);
        preferences.putString("Password_STA", password_sta);

    }

    String toString() {
        String s;

        s += "ssid=";
        s += getSSID();
        s += "\n";
        s += "password=";
        s += getPassword();
        s += "\n";
        s += "channel=";
        s += getChannel();
        s += "\n";

        return s;
    }

    const char* getSSID() {
        return ssid_ap.c_str();
    }

    const char* getPassword() {
        return password_ap.c_str();
    }

    const char* getChannel() {
        return channel.c_str();
    }

    int getChannelNum() {
        if (strcmp(channel.c_str(), "auto") != 0) return atoi(channel.c_str());
        return 1;
    }

    void set(const char* name, const char* value) {
        if (strcmp(name, "ssid") == 0) {
            setSSID(value);
        } else if (strcmp(name, "password") == 0) {
            setPassword(value);
        } else if (strcmp(name, "channel") == 0) {
            setChannel(value);
        }
    }

    void setSSID(const char* ssid) {
        if (ssid && (strlen(ssid) <= 33)) {
            ssid_ap = ssid;
            preferences.putString("SSID_AP", ssid_ap);
        }
    }

    void setPassword(const char* password) {
        if (password && (strlen(password) >= 8) && (strlen(password) <= 65)) {
            password_ap = password;
            preferences.putString("Password_AP", password_ap);
        }
    }

    void setChannel(const char* channels) {
        if (channels && ((strcmp(channels, "auto") == 0) || ((atoi(channels) >= 1) && (atoi(channels) <= 13))) && (strlen(channels) <= 5)) {
            channel = channels;
            preferences.putString("Channel", channel);
        }
    }

}
