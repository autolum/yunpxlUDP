#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial1);

#include "SPI.h"
#include "WS2801.h"

#define NPXLS 24

uint8_t dataPin  = 3;
uint8_t clockPin = 2;

Adafruit_WS2801 strip = Adafruit_WS2801(NPXLS, dataPin, clockPin);

byte rgb[100];

void setup() {
    SLIPSerial.begin(250000);   //this is the standard speed on the Yun
    Serial.begin(115200); // to  debug on usb port
}

void loop(){
    int l;
    byte s;
    if (SLIPSerial.available() > 0){
      int i = 0;
      while(!SLIPSerial.endofPacket()){
        rgb[i] = SLIPSerial.read();
        i++;
      }
    }
    
    Serial.println("--------");
    Serial.println(rgb[0]);
    Serial.println(rgb[1]);
    Serial.println(rgb[2]);
    
    int r = rgb[0];
    int g = rgb[1];
    int b = rgb[0];
    
    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
    Serial.println("--------");
    
    strip.setPixelColor(0, cRGB(r,g,b));
    
    strip.show();
}


uint32_t cRGB(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}
