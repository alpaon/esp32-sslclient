#include "Ethernet.h"

void resetW5500(uint8_t pin_rstn) {
    digitalWrite(pin_rstn, HIGH);
    delay(100);
    digitalWrite(pin_rstn, LOW);
    delay(100);
    digitalWrite(pin_rstn, HIGH);
    delay(200);
}

void generateEthernetMACAddress(byte *mac) {
    esp_read_mac(mac, ESP_MAC_ETH);

    mac[0] &= 0xFE;
    mac[0] |= 0x02;
}

uint8_t pin_rstn = 0xFF, pin_nss = 0xFF;

void ethernet_connect() {}

Client *ethernet_init(uint8_t _pin_rstn, uint8_t _pin_nss, char *static_ip,
                      char *dns_server, char *gateway_ip, char *subnet_mask,
                      bool use_dhcp) {
    pin_rstn = _pin_rstn;
    pin_nss = _pin_nss;

    byte mac[6];
    generateEthernetMACAddress(mac);

    resetW5500(pin_rstn);

    Ethernet.init(pin_nss); // SPI CS 핀 설정

    // while (Ethernet.hardwareStatus() == EthernetNoHardware) {
    //     Serial.printf("Ethernet interface was not found.\n");
    //     delay(1000);
    // }

    Serial.printf("Check Ethernet link ...");
    uint32_t start = millis();
    while (Ethernet.linkStatus() == LinkOFF) {
        Serial.printf(".");
        delay(1000);
    }
    Serial.printf("Done\n");

    if (use_dhcp) {
        Serial.printf("Configuring Ethernet using DHCP ...");
        while (Ethernet.begin(mac) != 1) {
            Serial.printf(".");
            delay(1000);
        }
        Serial.printf("Done\n");
    } else {
        Serial.printf("Configuring Ethernet using Static IP ");
        IPAddress ip;
        ip.fromString(static_ip);
        IPAddress dns;
        dns.fromString(dns_server);
        IPAddress gateway;
        gateway.fromString(gateway_ip);
        IPAddress subnet;
        subnet.fromString(subnet_mask);
        Ethernet.begin(mac, ip, dns, gateway, subnet);
        Serial.printf("Done\n");
    }

    ethernet_print_status();

    return new EthernetClient();
}

bool ethernet_loop() {
    if (Ethernet.linkStatus() != LinkON) {
        Serial.printf("Ethernet link is not connected.\n");
        delay(1000);

        esp_restart();
        return false;
    }

    return true;
}

void ethernet_print_status() {
    Serial.printf("  IP Address: %s\n", Ethernet.localIP().toString().c_str());
    Serial.printf("  Subnet Mask: %s\n",
                  Ethernet.subnetMask().toString().c_str());
    Serial.printf("  Gateway: %s\n", Ethernet.gatewayIP().toString().c_str());
    Serial.printf("  DNS Server: %s\n",
                  Ethernet.dnsServerIP().toString().c_str());
}
