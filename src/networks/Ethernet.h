#ifndef ETHERNET_MANAGER_H
#define ETHERNET_MANAGER_H

#include <Arduino.h>
#include <Ethernet.h>
#include <SPI.h>

struct EthernetInterface {
    uint8_t W5500_RSTN;
    uint8_t W5500_SPI_NSS;
};

Client *ethernet_init(uint8_t _pin_rstn, uint8_t _pin_nss, char *static_ip,
                      char *dns_server, char *gateway_ip, char *subnet_mask,
                      bool use_dhcp);
bool ethernet_loop();
void ethernet_print_status();

#endif
