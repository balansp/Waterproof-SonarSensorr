#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

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

SoftwareSerial mySerial(D2, D1); // RX, TX

unsigned char data[4] = {};

void setup() {
  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);
  Serial.begin(115200);
  mySerial.begin(9600);
}

float readDistance() {
  if (mySerial.available() >= 4) {
    for (int i = 0; i < 4; i++) {
      data[i] = mySerial.read();
    }
    if (data[0] == 0xff) {
      int sum = (data[0] + data[1] + data[2]) & 0xFF;
      if (sum == data[3]) {
        int distance = (data[1] << 8) + data[2];
        return distance / 10.0;
      }
    }
  }

  return -1;
}

void loop() {
  float distanceInCm = readDistance();
  
  if (distanceInCm >= 0) {
    Serial.println(distanceInCm);
  } else {
    Serial.println("Invalid data");
  }

  delay(100);
}
