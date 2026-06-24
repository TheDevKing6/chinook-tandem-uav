#include <Arduino.h>

const int PIN_THROTTLE = 32;
const int PIN_YAW      = 33;
const int PIN_PITCH    = 34;
const int PIN_ROLL     = 35;

struct __attribute__((__packed__)) RadioPacket {
    uint16_t throttle;
    uint16_t yaw;
    uint16_t pitch;
    uint16_t roll;
    uint8_t  checksum;
};

void setup() {
    Serial.begin(115200);
    
    analogSetAttenuation(ADC_11db);
    pinMode(PIN_THROTTLE, INPUT);
    pinMode(PIN_YAW, INPUT);
    pinMode(PIN_PITCH, INPUT);
    pinMode(PIN_ROLL, INPUT);
    
    Serial.println("STATUS: Custom ESP32 2.4GHz Transmitter Initialized.");
}

void loop() {
    RadioPacket txData;
    
    txData.throttle = analogRead(PIN_THROTTLE);
    txData.yaw      = analogRead(PIN_YAW);
    txData.pitch    = analogRead(PIN_PITCH);
    txData.roll     = analogRead(PIN_ROLL);
    
    txData.checksum = (txData.throttle + txData.yaw + txData.pitch + txData.roll) % 256;
    
    Serial.printf("LOG -> T:%d | Y:%d | P:%d | R:%d\n", txData.throttle, txData.yaw, txData.pitch, txData.roll);
    
    delay(10);
}
