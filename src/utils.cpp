#include "utils.h"

String payloadToString(byte *payload, unsigned int length) {
    char buf[length + 1] = {0};
    memcpy(buf, payload, length);
    return String(buf);
}

int countTokens(const String &input) {
    int count = 0;
    int startIndex = 0;
    int foundIndex = 0;

    while ((foundIndex = input.indexOf(' ', startIndex)) >= 0) {
        count++;
        startIndex = foundIndex + 1;
    }

    // 마지막 토큰 처리
    if (input.length() > startIndex) {
        count++;
    }

    return count;
}

void splitString(const String &input, String *result) {
    int startIndex = 0;
    int foundIndex = 0;
    int arrIndex = 0;

    while ((foundIndex = input.indexOf(' ', startIndex)) >= 0) {
        result[arrIndex++] = input.substring(startIndex, foundIndex);
        startIndex = foundIndex + 1;
    }

    // 마지막 토큰 처리
    result[arrIndex] = input.substring(startIndex);
}

String *parsePayload(byte *payload, unsigned int length, int &tokenCount) {
    String data = payloadToString(payload, length);
    tokenCount = countTokens(data);

    String *tokens = new String[tokenCount];
    splitString(data, tokens);

    return tokens;
}

String get_sn() {
    if (SN != NULL) {
        return SN;
    }

    uint32_t chipId = 0;

    for (int i = 0; i < 17; i = i + 8) {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }

    char buffer[7];

    // sprintf를 사용하여 chipId를 6자리 16진수 문자열로 포맷합니다.
    // %06X 형식 지정자는 결과가 6자리가 되도록 앞을 0으로 채웁니다.
    sprintf(buffer, "%06X", chipId);

    // String 객체를 만들고 대문자로 변환합니다.
    SN = String(buffer);
    SN.toUpperCase();
    return SN;
}

const char *get_reset_reason(int cpu_no) {
    RESET_REASON reason = rtc_get_reset_reason(cpu_no);
    switch (reason) {
    case 1:
        return ("Vbat power on reset");
    case 3:
        return ("Software reset digital core");
    case 4:
        return ("Legacy watch dog reset digital core");
    case 5:
        return ("Deep Sleep reset digital core");
    case 6:
        return ("Reset by SLC module, reset digital core");
    case 7:
        return ("Timer Group0 Watch dog reset digital core");
    case 8:
        return ("Timer Group1 Watch dog reset digital core");
    case 9:
        return ("RTC Watch dog Reset digital core");
    case 10:
        return ("Instrusion tested to reset CPU");
    case 11:
        return ("Time Group reset CPU");
    case 12:
        return ("Software reset CPU");
    case 13:
        return ("RTC Watch dog Reset CPU");
    case 14:
        return ("for APP CPU, reseted by PRO CPU");
    case 15:
        return ("Reset when the vdd voltage is not stable");
    case 16:
        return ("RTC Watch dog reset digital core and rtc module");
    default:
        return ("NO_MEAN");
    }
}