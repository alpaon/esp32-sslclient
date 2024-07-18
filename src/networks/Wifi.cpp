// wifi.cpp

#include "Wifi.h"

WiFiMulti wifiMulti;
wifi_credentials conf = {0};

Client *init_wifi(wifi_credentials wifi_config) {
    Serial.printf("[WiFi] initializing\n");

    Serial.printf("  SSID: %s\n", wifi_config.ssid);
    Serial.printf("  PASS: %s\n", wifi_config.pass);

    wifiMulti.addAP(wifi_config.ssid, wifi_config.pass);

    // conf = load_wifi_config();
    // load conf and add to wifiMulti
    // if (strlen(conf.ssid) > 0 && strlen(conf.pass) > 0) {
    //     Serial.printf("  User-defined WiFi credentials found.\n");
    //     Serial.printf("    SSID: %s\n", conf.ssid);
    //     Serial.printf("    PASS: %s\n", conf.pass);

    //     wifiMulti.addAP(conf.ssid, conf.pass);
    // }

    Serial.printf("[WiFi] Waiting for connection.\n");

    while (wifiMulti.run() != WL_CONNECTED) {
        delay(250);
    }
    Serial.printf("Done\n");

    Serial.printf("[WiFi] Connected!\n");

    WiFi_print_status();

    // WiFi.RSSI();

    return new WiFiClient();
}

const char *get_wifi_signal_strength(int rssi) {
    if (rssi >= -50) {
        return "Excellent";
    } else if (rssi >= -60) {
        return "Good";
    } else if (rssi >= -70) {
        return "Fair";
    } else if (rssi >= -80) {
        return "Weak";
    } else {
        return "Poor";
    }
}

void WiFi_print_status() {
    Serial.printf("  SSID: %s\n", WiFi.SSID().c_str());
    Serial.printf("  BSSID: %s\n", WiFi.BSSIDstr().c_str());
    Serial.printf("  IP address: %s\n", WiFi.localIP().toString().c_str());
    int8_t rssi = WiFi.RSSI();
    Serial.printf("  RSSI: %d (%s)\n", rssi, get_wifi_signal_strength(rssi));
    Serial.printf("  Channel: %d\n", WiFi.channel());
    Serial.printf("  Subnet Mask: %s\n", WiFi.subnetMask().toString().c_str());
    Serial.printf("  Gateway IP: %s\n", WiFi.gatewayIP().toString().c_str());
    Serial.printf("  DNS 1: %s\n", WiFi.dnsIP().toString().c_str());
    Serial.printf("  MAC address: %s\n", WiFi.macAddress().c_str());
    Serial.printf("  WiFi hostname: %s\n", WiFi.getHostname());
    // Serial.printf("  WiFi status: %d\n", WiFi.status());
    // Serial.printf("  WiFi mode: %d\n", WiFi.getMode());
    // Serial.printf("  WiFi sleep mode: %d\n", WiFi.getSleep());
    Serial.printf("  WiFi TX power: %d\n", WiFi.getTxPower());
    Serial.printf("\n");
}

void wifi_check() {
    if (WiFi.status() != WL_CONNECTED) {
        uint32_t wifi_start_timer = millis();

        Serial.printf("[WiFi] connection lost\n");

        esp_restart();
        // init_wifi();
        // ESP.restart();

        // while (wifiMulti.run() != WL_CONNECTED) {
        //     if (millis() - wifi_start_timer > WIFI_TIMEOUT) {
        //         Serial.printf("\n");
        //         Serial.printf("WiFi connection failed: timeout\n");
        //         ESP.restart();
        //     }

        //     Serial.printf(".");
        //     delay(500);
        // }
        // Serial.printf("\n");
    }

    // if (WiFi.status() == WL_CONNECTED) {
    // }
}