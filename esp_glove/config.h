/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
 */

#pragma once

#define VERSION "0.1"

/*! ===== DEBUG Settings ===== */
#define ENABLE_DEBUG
#define DEBUG_LED 2
#define DEBUG_PORT Serial
#define DEBUG_BAUD 115200

/*! ===== WiFi AP-MODE Settings ===== */
#define WIFI_SSID "Glove"
#define WIFI_PASSWORD "glove123"
#define WIFI_CHANNEL "1"

#define HOSTNAME "Glove"
#define URL "glove.local"

/*! ===== WiFi STA-MODE Settings ===== */
#define NETWORK_SSID ""
#define NETWORK_PASSWORD ""

/*! ===== Temperature Settings ===== */
#define TARGET_TEMP 25
#define APIKEY 
#define TEMP1PIN 
#define TEMP2PIN

/*! ===== LED Settings ===== */


/*! ===== Button Settings ===== */
#define BUTTON1PIN 18
#define BUTTON2PIN 23

/*! ===== Battery Settings ===== */
#define CELLONE 34
#define CELLTWO 33
#define MINVOLTAGE 2.7
#define MAXVOLTAGE 3.65

#if !defined(ESP32)
#error You are compiling for the wrong board, mate! Select something with an ESP32.
#endif
