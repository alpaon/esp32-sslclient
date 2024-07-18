#ifndef PIN_MAP_H
#define PIN_MAP_H

#include "Version.h"
#include "secret.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#if HW_VERSION_CODE == HW_VERSION_CODE_1_0_0
// GPIO breakout pins reserved for future use
#define PIN_GPIO9 9
#define PIN_GPIO10 10
#define PIN_GPIO11 11
#define PIN_GPIO12 12

// WS2812 RGB LED
#define PIN_RGB_LED 48

// config button
#define PIN_BOOT 0

// I2C for BME280 and ENS160
#define PIN_SDA PIN_GPIO9
#define PIN_SCL PIN_GPIO10

// CodeZoo Cat.M1
#define PIN_LTE_UART_RXD 18 // IO18  LTE TXD, ESP32 RXD
#define PIN_LTE_UART_TXD 17 // IO17: LTE RXD, ESP32 TXD
#define PIN_LTE_MWAKEUP 46
#define PIN_LTE_LDO_EN 8
#define PIN_LTE_MRESET 3

// W5500 Ethernet
#define PIN_SPI_MOSI 35
#define PIN_SPI_SCK 36
#define PIN_SPI_MISO 37
#define PIN_W5500_RSTN 38
#define PIN_W5500_SPI_NSS 6

// CH340/RS485
#define PIN_UART_RXD 43
#define PIN_UART_TXD 44

#define PIN_RS485_DE 5 // DE & !RE

#elif HW_VERSION_CODE == HW_VERSION_CODE_1_0_1
// GPIO breakout pins reserved for future use
#define PIN_GPIO9 9
#define PIN_GPIO10 10
#define PIN_GPIO11 11
#define PIN_GPIO12 12
#define PIN_GPIO13 13
#define PIN_GPIO14 14
#define PIN_GPIO21 21
#define PIN_GPIO47 47

// WS2812 RGB LED
#define PIN_RGB_LED 48

// Network status LED, config button
#define PIN_LED_NETWORK_IND 7
#define PIN_BTN_CONFIG 2
#define PIN_BOOT 0

// I2C for BME280 and ENS160
#define PIN_SDA PIN_GPIO9
#define PIN_SCL PIN_GPIO10

// CodeZoo Cat.M1
#define PIN_LTE_UART_RXD 18 // IO18  LTE TXD, ESP32 RXD
#define PIN_LTE_UART_TXD 17 // IO17: LTE RXD, ESP32 TXD
#define PIN_LTE_MWAKEUP 46
#define PIN_LTE_LDO_EN 8
#define PIN_LTE_MRESET 3

// W5500 Ethernet
#define PIN_SPI_MOSI 35
#define PIN_SPI_SCK 36
#define PIN_SPI_MISO 37
#define PIN_W5500_RSTN 38
#define PIN_W5500_SPI_NSS 6

// CH340/RS485
#define PIN_UART_RXD 44
#define PIN_UART_TXD 43

#define PIN_RS485_DE 5 // DE & !RE

#else
#error "Unknown HW_VERSION_CODE"
#endif // HW_VERSION_CODE

void init_pins();

void init_serial();

#endif // PIN_MAP_H