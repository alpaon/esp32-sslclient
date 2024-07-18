// Wifi.h

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <FS.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <WiFiMulti.h>

struct wifi_credentials {
    char ssid[32];
    char pass[64];
};

Client *init_wifi(wifi_credentials wifi_config);
void WiFi_print_status();
void wifi_check();

#endif // WIFI_H
