 
#include <Arduino.h>
#include <SoftwareSerial.h>
/* 
White - Green - RX
Yellow - Blue - TX
Red - Red - VCC
Black - Black - GND
*/
SoftwareSerial mySerial(D2,D3); // RX, TX
unsigned char data[4]={};
float distance;

int getDistance(){
  do{
     for(int i=0;i<4;i++){
       data[i]=mySerial.read();
     }
  }while(mySerial.read()==0xff);

  mySerial.flush();

  if(data[0]==0xff){
      int sum;
      sum=(data[0]+data[1]+data[2])&0x00FF;
      if(sum==data[3])  {
        distance=(data[1]<<8)+data[2];
        if(distance>30)  {
           distance= distance/10;
          // Serial.print("distance="+ String(distance) + "cm");
          } else  {
            Serial.println("Below the lower limit");
            distance = 0;
          }
      } else {
      //  distance = -1;
        Serial.println("Error!");
      }
     }

  return  distance;
}
void setup()
{
 Serial.begin(9600);
 mySerial.begin(9600); 
}

void loop()
{
    Serial.println(getDistance());
    delay(100);
}
