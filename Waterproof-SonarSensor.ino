#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

/*
 ---------------------------
 | ESP     WIRE      SONAR |
 ---------------------------
 D0   = RED RED = VCC
 GND  = BLK BLK = GND
 D1   = BLU YLW = Tx 
 D2   = GRN WHT = Rx 
 ---------------------------
*/

SoftwareSerial mySerial(D2, D1); // RX, TX

unsigned char data[4] = {};

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600); 
}

float readDistance() {
  do {
    for (int i = 0; i < 4; i++) {
      data[i] = mySerial.read();
    }
  } while (mySerial.read() == 0xff);

  mySerial.flush();

  if (data[0] == 0xff) {
    int sum = (data[0] + data[1] + data[2]) & 0x00FF;
    if (sum == data[3]) {
      float distance = (data[1] << 8) + data[2];
      return distance / 10;
    }
  }

  return -1;
}

void loop() {
  float distance = readDistance();
  if (distance >=0) {
    Serial.println(distance);
  }  

  delay(100);
}
