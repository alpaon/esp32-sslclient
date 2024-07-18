#include "PinMap.h"
#include "secret.h"

void init_pins() {
#if HW_VERSION_CODE == HW_VERSION_CODE_1_0_0
    pinMode(PIN_BOOT, INPUT_PULLUP);

    pinMode(PIN_LTE_MWAKEUP, OUTPUT);
    pinMode(PIN_LTE_LDO_EN, OUTPUT);
    pinMode(PIN_LTE_MRESET, OUTPUT);
    digitalWrite(PIN_LTE_MWAKEUP, HIGH);
    digitalWrite(PIN_LTE_LDO_EN, HIGH);
    digitalWrite(PIN_LTE_MRESET, HIGH);

    pinMode(PIN_RS485_DE, OUTPUT);
    digitalWrite(PIN_RS485_DE, LOW);

    pinMode(PIN_W5500_RSTN, OUTPUT);
    pinMode(PIN_W5500_SPI_NSS, OUTPUT);
    digitalWrite(PIN_W5500_RSTN, HIGH);
    digitalWrite(PIN_W5500_SPI_NSS, HIGH);

    pinMode(PIN_GPIO9, OUTPUT);
    pinMode(PIN_GPIO10, OUTPUT);
    pinMode(PIN_GPIO11, OUTPUT);
    pinMode(PIN_GPIO12, OUTPUT);
    digitalWrite(PIN_GPIO9, LOW);
    digitalWrite(PIN_GPIO10, LOW);
    digitalWrite(PIN_GPIO11, LOW);
    digitalWrite(PIN_GPIO12, LOW);

    // I2C for BME280 and ENS160
    Wire.begin(PIN_SDA, PIN_SCL);

    // SPI for W5500 Ethernet
    SPI.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI, PIN_W5500_SPI_NSS);
#elif HW_VERSION_CODE == HW_VERSION_CODE_1_0_1
    pinMode(PIN_BOOT, INPUT_PULLUP);

    pinMode(PIN_LTE_MWAKEUP, OUTPUT);
    pinMode(PIN_LTE_LDO_EN, OUTPUT);
    pinMode(PIN_LTE_MRESET, OUTPUT);
    digitalWrite(PIN_LTE_MWAKEUP, HIGH);
    digitalWrite(PIN_LTE_LDO_EN, HIGH);
    digitalWrite(PIN_LTE_MRESET, HIGH);

    pinMode(PIN_RS485_DE, OUTPUT);
    digitalWrite(PIN_RS485_DE, LOW);

    pinMode(PIN_W5500_RSTN, OUTPUT);
    pinMode(PIN_W5500_SPI_NSS, OUTPUT);
    digitalWrite(PIN_W5500_RSTN, HIGH);
    digitalWrite(PIN_W5500_SPI_NSS, HIGH);

    pinMode(PIN_GPIO9, OUTPUT);
    pinMode(PIN_GPIO10, OUTPUT);
    pinMode(PIN_GPIO11, OUTPUT);
    pinMode(PIN_GPIO12, OUTPUT);
    pinMode(PIN_GPIO13, OUTPUT);
    pinMode(PIN_GPIO14, OUTPUT);
    pinMode(PIN_GPIO21, OUTPUT);
    pinMode(PIN_GPIO47, OUTPUT);
    digitalWrite(PIN_GPIO9, LOW);
    digitalWrite(PIN_GPIO10, LOW);
    digitalWrite(PIN_GPIO11, LOW);
    digitalWrite(PIN_GPIO12, LOW);
    digitalWrite(PIN_GPIO13, LOW);
    digitalWrite(PIN_GPIO14, LOW);
    digitalWrite(PIN_GPIO21, LOW);
    digitalWrite(PIN_GPIO47, LOW);

    pinMode(PIN_LED_NETWORK_IND, OUTPUT);
    digitalWrite(PIN_LED_NETWORK_IND, LOW);
    pinMode(PIN_BTN_CONFIG, INPUT_PULLUP);

    // I2C for BME280 and ENS160
    Wire.begin(PIN_SDA, PIN_SCL);

    // SPI for W5500 Ethernet
    SPI.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI, PIN_W5500_SPI_NSS);
#else
#error "Unknown HW_VERSION_CODE"
#endif
    // Serial 설정은 변경될 수 있기에 전처리기 밖으로 빼놓음

    Serial.begin(115200); // native USB
    Serial1.begin(115200, SERIAL_8N1, PIN_LTE_UART_RXD,
                  PIN_LTE_UART_TXD); // LTE
    // Serial2.begin(115200, SERIAL_8N1, PIN_UART_RXD,
    //               PIN_UART_TXD); // CH340/RS485
    // HardwareSerial SerialPort(1);

    // Serial.println("Native USB-UART connection initialized");  // native USB
    // Serial1.println("CH340 USB-UART connection initialized");  // CH340
    // Serial2.println("Serial2 initialized");  // RS485

    // while(Serial.available()==0){  // wait for native USB
    //     delay(1);
    // }
}

void init_serial() {
    const int TIMEOUT_SERIAL_CONNECT = 4000; // 추후 필요에 따라 define 하도록

    // delay(1000);
    uint32_t serial_start_timer = millis();

    // USB Serial Connection 수립시까지 대기
    // 대기중에는 LED를 깜빡이도록 함
    while (!Serial) {
        uint32_t elapsed = millis() - serial_start_timer;
        if (elapsed > TIMEOUT_SERIAL_CONNECT) {
            // log("Serial connection failed: timeout\n");
            // led_set(5, 0, 0); // red
            // ESP.restart();
            break;
        }
    }
    delay(250);
    int32_t delay_time = 1000 - (millis() - serial_start_timer);
    if (delay_time > 0) {
        delay(delay_time);
    }
}