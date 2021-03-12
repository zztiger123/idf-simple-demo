# HTTP Proxy Example

Uses a POSIX socket to make a very simple HTTP request by HTTP proxy.

IDF Version ： release/v4.2 (commit id : 2aafcd9b1f18dce8cefae8087cd0e5302c64b00c)

Before using this example, you only need to set the Wi-Fi SSID and PASSWORD in menuconfig and modify the following macro definitions ：

1. Configure proxy server information

The [free HTTP proxy server](http://free-proxy.cz/zh/proxylist/country/all/http/ping/all) used here. Need to configure the ip port number and other information corresponding to the http proxy server, the example is as follows :

```c
#define WEB_SERVER "159.65.228.74"
#define WEB_PORT "80"
#define WEB_PATH "/"
```

Here is the http URL that needs to be accessed, here is the URL of the ESP selection tool as an example :

```c
/* Constants that aren't configurable in menuconfig */
#define ORIG_WEB_SERVER "www.baidu.com"
#define ORIG_WEB_PORT "80"
#define ORIG_WEB_PATH "/"

static const char *REQUEST = "GET " ORIG_WEB_PATH " HTTP/1.0\r\n"
    "Host: "ORIG_WEB_SERVER":"ORIG_WEB_PORT"\r\n"
    "User-Agent: esp-idf/1.0 esp32\r\n"
    "\r\n";
```

After configuring the environment of esp-idf 4.2, enter `idf.py menuconfig` in terminal and set `WiFi SSID` and `WiFi Password` in `menuconfig -> Example Connection Configuration`. And then enter `idf.py build` and `idf.py flash monitor` in the terminal. Finally, you can see the following log in monitor :

```shell
I (0) cpu_start: App cpu up.
I (443) heap_init: Initializing. RAM available for dynamic allocation:
I (450) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (456) heap_init: At 3FFB7DC0 len 00028240 (160 KiB): DRAM
I (462) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (468) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (475) heap_init: At 400955BC len 0000AA44 (42 KiB): IRAM
I (481) cpu_start: Pro cpu start user code
I (499) spi_flash: detected chip: generic
I (500) spi_flash: flash io: dio
W (500) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (511) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (616) wifi:wifi driver task: 3ffc030c, prio:23, stack:6656, core=0
I (616) system_api: Base MAC address is not set
I (616) system_api: read default base MAC address from EFUSE
I (636) wifi:wifi firmware version: 1865b55
I (636) wifi:wifi certification version: v7.0
I (636) wifi:config NVS flash: enabled
I (646) wifi:config nano formating: disabled
I (646) wifi:Init data frame dynamic rx buffer num: 32
I (646) wifi:Init management frame dynamic rx buffer num: 32
I (656) wifi:Init management short buffer num: 32
I (656) wifi:Init dynamic tx buffer num: 32
I (666) wifi:Init static rx buffer size: 1600
I (666) wifi:Init static rx buffer num: 10
I (676) wifi:Init dynamic rx buffer num: 32
I (676) wifi_init: rx ba win: 6
I (676) wifi_init: tcpip mbox: 32
I (686) wifi_init: udp mbox: 6
I (686) wifi_init: tcp mbox: 6
I (686) wifi_init: tcp tx win: 5744
I (696) wifi_init: tcp rx win: 5744
I (696) wifi_init: tcp mss: 1440
I (706) wifi_init: WiFi IRAM OP enabled
I (706) wifi_init: WiFi RX IRAM OP enabled
I (716) example_connect: Connecting to zztest...
I (816) phy: phy_version: 4500, 0cd6843, Sep 17 2020, 15:37:07, 0, 0
I (816) wifi:mode : sta (24:62:ab:e2:55:10)
I (816) example_connect: Waiting for IP(s)
I (936) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1
I (946) wifi:state: init -> auth (b0)
I (956) wifi:state: auth -> assoc (0)
I (956) wifi:state: assoc -> run (10)
I (996) wifi:connected with zztest, aid = 2, channel 6, BW20, bssid = 08:60:6e:21:48:e8
I (996) wifi:security: WPA2-PSK, phy: bgn, rssi: -26
I (996) wifi:pm start, type: 1

I (1096) wifi:AP's beacon interval = 102400 us, DTIM period = 3
I (2106) esp_netif_handlers: example_connect: sta ip: 192.168.1.8, mask: 255.255.255.0, gw: 192.168.1.1
I (2106) example_connect: Got IPv4 event: Interface "example_connect: sta" address: 192.168.1.8
I (2606) example_connect: Got IPv6 event: Interface "example_connect: sta" address: fe80:0000:0000:0000:2662:abff:fee2:5510, type: ESP_IP6_ADDR_IS_LINK_LOCAL
I (2606) example_connect: Connected to example_connect: sta
I (2616) example_connect: - IPv4 address: 192.168.1.8
I (2616) example_connect: - IPv6 address: fe80:0000:0000:0000:2662:abff:fee2:5510, type: ESP_IP6_ADDR_IS_LINK_LOCAL
I (2636) example: DNS lookup succeeded. IP=159.65.228.74
I (2636) example: ... allocated socket
I (2956) example: ... connected
I (2956) example: ... socket send success
I (2956) example: ... set socket receiving timeout success
HTTP/1.1 200 OK
Date: Fri, 12 Mar 2021 07:54:31 GMT
Server: Apache/2.4.41 (Ubuntu)
Last-Modified: Wed, 30 Dec 2020 02:20:17 GMT
ETag: "96c7-5b7a525ee4077"
Accept-Ranges: bytes
Content-Length: 38599
Vary: Accept-Encoding
Connection: close
Content-Type: text/html

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8" />
    <meta
      name="viewport"
      content="width=device-width, initial-scale=1.0, user-scalable=0"
```