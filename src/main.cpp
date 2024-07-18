#include "secret.h"

#include "PinMap.h"
#include "certificates.h"
#include "networks/Ethernet.h"
#include "networks/Wifi.h"
#include <Arduino.h>
#include <SSLClient.h>
#include <time.h>

void setup();
void loop();

EthernetInterface ethernetInterface = {
    .W5500_RSTN = PIN_W5500_RSTN,
    .W5500_SPI_NSS = PIN_W5500_SPI_NSS,
};

Client *client = nullptr;
SSLClient *ssl_client = nullptr;

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 32400;
const int daylightOffset_sec = 0;

unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;

char *server_host = "ifconfig.me";

void connect_network_wifi() {
    wifi_credentials wifi_cred;
    strncpy(wifi_cred.ssid, WIFI_SSID, sizeof(wifi_cred.ssid) - 1);
    wifi_cred.ssid[sizeof(wifi_cred.ssid) - 1] = '\0';
    strncpy(wifi_cred.pass, WIFI_PASSWORD, sizeof(wifi_cred.pass) - 1);
    wifi_cred.pass[sizeof(wifi_cred.pass) - 1] = '\0';
    client = init_wifi(wifi_cred);
}

void connect_network_ethernet() {
    client = ethernet_init(ethernetInterface.W5500_RSTN,
                           ethernetInterface.W5500_SPI_NSS, ETHERNET_STATIC_IP,
                           ETHERNET_DNS_SERVER, ETHERNET_GATEWAY,
                           ETHERNET_SUBNET_MASK, ETHERNET_USE_DHCP);
}

void setup() {
    init_pins();
    init_serial();

    connect_network_wifi();
    // connect_network_ethernet();

    ssl_client = new SSLClient(*client, TAs, (size_t)TAs_NUM, A5, 0,
                               SSLClient::SSL_DUMP);

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
        Serial.printf("Current time: %04d-%02d-%02d %02d:%02d:%02d\n",
                      timeinfo.tm_year + 1900, timeinfo.tm_mon + 1,
                      timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min,
                      timeinfo.tm_sec);
    } else {
        Serial.println("Failed to obtain time");
    }

    auto start = millis();
    if (ssl_client->connect(server_host, 443)) {
        auto time = millis() - start;
        Serial.print("Took: ");
        Serial.println(time);
        // Make a HTTP request:
        ssl_client->println("GET / HTTP/1.1");
        ssl_client->println("User-Agent: SSLClientOverEthernet");
        ssl_client->print("Host: ");
        ssl_client->println(server_host);
        ssl_client->println("Connection: close");
        ssl_client->println();
    } else {
        // if you didn't get a connection to the server:
        Serial.println("connection failed");
    }
}

void loop() {
    // if there are incoming bytes available
    // from the server, read them and print them:
    int len = ssl_client->available();
    if (len > 0) {
        byte buffer[80];
        if (len > 80)
            len = 80;
        ssl_client->read(buffer, len);
        if (printWebData) {
            Serial.write(buffer,
                         len); // show in the serial monitor (slows some boards)
        }
        byteCount = byteCount + len;
    }

    // if the server's disconnected, stop the client:
    if (!ssl_client->connected()) {
        endMicros = micros();
        Serial.println();
        Serial.println("disconnecting.");
        ssl_client->stop();
        Serial.print("Received ");
        Serial.print(byteCount);
        Serial.print(" bytes in ");
        float seconds = (float)(endMicros - beginMicros) / 1000000.0;
        Serial.print(seconds, 4);
        float rate = (float)byteCount / seconds / 1000.0;
        Serial.print(", rate = ");
        Serial.print(rate);
        Serial.print(" kbytes/second");
        Serial.println();

        // do nothing forevermore:
        while (true) {
            delay(1);
        }
    }
}