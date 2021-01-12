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
#define ORIG_WEB_SERVER "http://products.espressif.com:8000/#/product-selector?language=en"
#define ORIG_WEB_PORT "80"
#define ORIG_WEB_PATH "/"

static const char *REQUEST = "GET " ORIG_WEB_PATH " HTTP/1.0\r\n"
    "Host: "ORIG_WEB_SERVER":"ORIG_WEB_PORT"\r\n"
    "User-Agent: esp-idf/1.0 esp32\r\n"
    "\r\n";
```

After configuring the environment of esp-idf 4.2, enter `idf.py menuconfig` in terminal and set `WiFi SSID` and `WiFi Password` in `menuconfig -> Example Connection Configuration`. And then enter `idf.py build` and `idf.py flash monitor` in the terminal. Finally, you can see the following log in monitor :

```shell

```