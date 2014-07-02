#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial1);

#include "SPI.h"
#include "WS2801.h"

#define NPXLS 24

uint8_t dataPin  = 3;
uint8_t clockPin = 2;

Adafruit_WS2801 strip = Adafruit_WS2801(NPXLS, dataPin, clockPin);

void setup() {
    SLIPSerial.begin(250000);   //this is the standard speed on the Yun
    Serial.begin(115200); // to  debug on usb port
}

void loop(){
    int l;
    byte s;
    byte rgb[100];

    while(!SLIPSerial.endofPacket())
        if( (l =SLIPSerial.available()) > 0)
        {
            for(int i = 0; i < l; i++){
              s = SLIPSerial.read();
              rgb[i] = s;
              //Serial.println(s);
            }
        }
    
    for (int i = 0; i < 24; i++){
      //Serial.println(rgb);
      strip.setPixelColor(i, cRGB(rgb[i*3],rgb[i*3+1],rgb[i*3+2]));
    }
    
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
