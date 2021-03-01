# WiFi Set country code example

(See the README.md file in the upper level 'examples' directory for more information about examples.)


## How to use example

### Configure the project

```
idf.py menuconfig
```

* Set WiFi SSID and WiFi Password and Maximum retry under Example Configuration Options.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.

> note : you can enable multiple PHY init data bin found in `Component config > PHY > CONFIG_ESP32_PHY_INIT_DATA_IN_PARTITION`.

## Example Output
Note that the output, in particular the order of the output, may vary depending on the environment.

Console output if station connects to AP successfully:
```
I (564) wifi station: ESP_WIFI_MODE_STA
I (584) wifi:wifi driver task: 3ffc0538, prio:23, stack:6656, core=0
I (584) system_api: Base MAC address is not set
I (584) system_api: read default base MAC address from EFUSE
I (604) wifi:wifi firmware version: 1865b55
I (604) wifi:wifi certification version: v7.0
I (604) wifi:config NVS flash: enabled
I (604) wifi:config nano formating: disabled
I (614) wifi:Init data frame dynamic rx buffer num: 32
I (614) wifi:Init management frame dynamic rx buffer num: 32
I (624) wifi:Init management short buffer num: 32
I (624) wifi:Init dynamic tx buffer num: 32
I (634) wifi:Init static rx buffer size: 1600
I (634) wifi:Init static rx buffer num: 10
I (634) wifi:Init dynamic rx buffer num: 32
I (644) wifi_init: rx ba win: 6
I (644) wifi_init: tcpip mbox: 32
I (654) wifi_init: udp mbox: 6
I (654) wifi_init: tcp mbox: 6
I (654) wifi_init: tcp tx win: 5744
I (664) wifi_init: tcp rx win: 5744
I (664) wifi_init: tcp mss: 1440
I (674) wifi_init: WiFi IRAM OP enabled
I (674) wifi_init: WiFi RX IRAM OP enabled
I (684) wifi:set country: cc=JP schan=1 nchan=14 policy=1

I (934) phy: phy_version: 4500, 0cd6843, Sep 17 2020, 15:37:07, 0, 2
W (934) phy_init: saving new calibration data because of checksum failure, mode(0)
I (954) wifi:mode : sta (30:ae:a4:80:21:3c)
I (964) wifi station: wifi_init_sta finished.
I (1084) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1
I (1084) wifi:state: init -> auth (b0)
I (1094) wifi:state: auth -> assoc (0)
I (1114) wifi:state: assoc -> run (10)
I (1144) wifi:connected with zztest, aid = 1, channel 6, BW20, bssid = 08:60:6e:21:48:e8
I (1144) wifi:security: WPA2-PSK, phy: bgn, rssi: -45
I (1144) wifi:pm start, type: 1

I (1174) wifi:AP's beacon interval = 102400 us, DTIM period = 3
I (2074) esp_netif_handlers: sta ip: 192.168.1.242, mask: 255.255.255.0, gw: 192.168.1.1
I (2074) wifi station: got ip:192.168.1.242
I (2074) wifi station: connected to ap SSID:zztest password:espressif
I (2084) wifi:state: run -> init (0)
I (2084) wifi:pm stop, total sleep time: 706579 us / 936356 us

I (2094) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1
W (2094) wifi:hmac tx: stop, discard
I (2154) wifi:flush txq
I (2154) wifi:stop sw txq
I (2154) wifi:lmac stop hw txq
I (2164) wifi:mode : sta (30:ae:a4:80:21:3c)
I (2164) wifi:set country: cc=USA schan=1 nchan=11 policy=1
```
