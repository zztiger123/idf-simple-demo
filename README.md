# ESP32 Wi-Fi AP+STA DEMO

IDF Version : release/v4.2
IDF Commit : 2532ddd9f447f6fab02bc2d1654534a7621e033a

## How to use example

### Configure the project

```
idf.py menuconfig
```

* Set WiFi STA SSID, WiFi STA Password, WiFi AP SSID and WiFi AP Password under Example Configuration Options.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.