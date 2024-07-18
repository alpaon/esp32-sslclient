#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

#ifndef PPRINTF_BUFSIZE
#define PPRINTF_BUFSIZE 64
#endif

#ifdef ESP_IDF_VERSION_MAJOR // IDF 4+
#if CONFIG_IDF_TARGET_ESP32  // ESP32/PICO-D4
#include <esp32/rom/rtc.h>
#elif CONFIG_IDF_TARGET_ESP32S2
#include <esp32s2/rom/rtc.h>
#elif CONFIG_IDF_TARGET_ESP32C3
#include <esp32c3/rom/rtc.h>
#elif CONFIG_IDF_TARGET_ESP32S3
#include <esp32s3/rom/rtc.h>
#else
#error Target CONFIG_IDF_TARGET is not supported
#endif
#else // ESP32 Before IDF 4.0
#include <rom/rtc.h>
#endif

int countTokens(const String &input);
void splitString(const String &input, String *result);
String payloadToString(byte *payload, unsigned int length);
String *parsePayload(byte *payload, unsigned int length, int &tokenCount);

static String SN;
String get_sn();
const char *get_reset_reason(int cpu_no = 0);

#endif // UTILS_H