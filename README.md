# GardenGlove
This repository contains all the code for a smart gardening glove designed by a group of students. In particular, the glove is to be controlled by an ESP32 and this repo contains the code for it.

## Installation
To install the code on our own ESP32, you will, of course, need the arduino ESP32 core libraries and 3 additional external libraries namely:
- https://github.com/spacehuhn/SimpleCLI
- https://github.com/me-no-dev/AsyncTCP
- https://github.com/me-no-dev/ESPAsyncWebServer
These libraries can be installed by cloning the repository, renaming the resulting folder (eg. SimpleCLI-master to SimpleCLI) and putting these folders in ~/Arduino/libraries. Now, the code will compile and can be uploaded to your ESP32.

## The structure
The following is an explanation of the file structure and what goes where:
```bash
|
|- esp_glove # contains the code that is to be uploaded to the ESP32
|- nvs_erase # contains a simple piece of code that resets the flash memory of ESP32
|- web # Contains the source code for the web application
...
|- webconverter.py # This converts the files located in web/ to the single file esp_glove/webfiles.h
```

