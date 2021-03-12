# WiFi Set country code example
## How to use example

IDF git commit : c40f2590b (HEAD, tag: v4.2) Merge branch 'featrue/remove_esp32-S2_preview_v4.2' into 'release/v4.2'
### Configure the project

```
idf.py menuconfig
```

* Set WiFi SSID and WiFi Password and Maximum retry under Example Configuration Options.

> note : We enable multiple PHY init data bin found in `Component config > PHY > CONFIG_ESP32_PHY_INIT_DATA_IN_PARTITION` by default.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.



## Example Output
Note that the output, in particular the order of the output, may vary depending on the environment.

Console output if station connects to AP successfully:
```
I (504) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (535) wifi station: ESP_WIFI_MODE_STA
I (555) wifi:wifi driver task: 3ffc0304, prio:23, stack:6656, core=0
I (555) system_api: Base MAC address is not set
I (555) system_api: read default base MAC address from EFUSE
I (655) wifi:wifi firmware version: 1865b55
I (655) wifi:wifi certification version: v7.0
I (655) wifi:config NVS flash: enabled
I (655) wifi:config nano formating: disabled
I (655) wifi:Init data frame dynamic rx buffer num: 32
I (655) wifi:Init management frame dynamic rx buffer num: 32
I (665) wifi:Init management short buffer num: 32
I (665) wifi:Init dynamic tx buffer num: 32
I (675) wifi:Init static rx buffer size: 1600
I (675) wifi:Init static rx buffer num: 10
I (685) wifi:Init dynamic rx buffer num: 32
I (685) wifi_init: rx ba win: 6
I (685) wifi_init: tcpip mbox: 32
I (695) wifi_init: udp mbox: 6
I (695) wifi_init: tcp mbox: 6
I (705) wifi_init: tcp tx win: 5744
I (705) wifi_init: tcp rx win: 5744
I (705) wifi_init: tcp mss: 1440
I (715) wifi_init: WiFi IRAM OP enabled
I (715) wifi_init: WiFi RX IRAM OP enabled
I (725) wifi:set country: cc=JP schan=1 nchan=14 policy=1

W (755) phy_init: failed to load RF calibration data (0xffffffff), falling back to full calibration
I (1005) phy: phy_version: 4500, 0cd6843, Sep 17 2020, 15:37:07, 0, 2
I (1075) wifi:mode : sta (24:62:ab:e2:55:10)
I (1075) wifi station: wifi_init_sta finished.
I (1805) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1
I (3355) wifi:state: init -> auth (b0)
I (3365) wifi:state: auth -> assoc (0)
I (3375) wifi:state: assoc -> run (10)
I (3415) wifi:connected with zztest, aid = 2, channel 6, BW20, bssid = 08:60:6e:21:48:e8
I (3415) wifi:security: WPA2-PSK, phy: bgn, rssi: -36
I (3425) wifi:pm start, type: 1

I (3495) wifi:AP's beacon interval = 102400 us, DTIM period = 3
I (7035) esp_netif_handlers: sta ip: 192.168.1.8, mask: 255.255.255.0, gw: 192.168.1.1
I (7035) wifi station: got ip:192.168.1.8
I (7035) wifi station: connected to ap SSID:zztest password:espressif
I (7045) wifi:state: run -> init (0)
I (7045) wifi:pm stop, total sleep time: 2896107 us / 3620355 us

I (7055) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1
I (7125) wifi:flush txq
I (7125) wifi:stop sw txq
I (7125) wifi:lmac stop hw txq
I (7125) wifi:set country: cc=USA schan=1 nchan=11 policy=1

I (7135) wifi:mode : sta (24:62:ab:e2:55:10)
```
