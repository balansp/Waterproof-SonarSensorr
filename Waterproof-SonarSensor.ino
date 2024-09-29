/*
---------------------------
| ESP  |  WIRE  |  SONAR  |
---------------------------
| D0   |  RED   |  VCC    |
| GND  |  BLK   |  GND    |
| D1   |  BLU   |  Tx     |
| D2   |  GRN   |  Rx     |
---------------------------
*/
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define SONAR_RX D2
#define SONAR_TX D1
SoftwareSerial sonar(SONAR_RX, SONAR_TX);

unsigned char data[4] = {};

float readDistance() {
    float distance = -1;
    if (sonar.available() >= 4) {
        for (int i = 0; i < 4; i++) {
            data[i] = sonar.read();
        }

        sonar.flush();

        if (data[0] == 0xff) {
            int sum = (data[0] + data[1] + data[2]) & 0x00FF;
            if (sum == data[3]) {
                distance = (data[1] << 8) + data[2];
                if (distance > 30) {
                    return distance / 10;
                }
            }
        }
    }
    return distance;
}

void setup() {
    pinMode(D0, OUTPUT);
    digitalWrite(D0, HIGH);
    Serial.begin(115200);
    sonar.begin(9600);
    delay(1000);
}

void loop() {
    float distance = readDistance();
    if (distance > 0) {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
    } 

    delay(500);
}

