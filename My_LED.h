#include <cmath>
#include "esp32-hal.h"

void myHSVtoRGB(float h, float s, float v, int *r, int *g, int *b) {

  // Are we just white?
  if (s < 20) {
    *r = *g = *b = 255 * v;
    return;
  }

  int i;
  float bright = (v/100);
  float sat = (s/100);
  h /= 60;
  i = floor(h);

  float f, p, q, t;
  f = h - i;
  p = bright * (1 - sat);
  q = bright * (1 - sat * f);
  t = bright * (1- sat * (1 - f));

  // Simply figure out which quadrant we are in
  switch (i % 6) {
    case 0:
      // Red
      *r = 255 * bright;
      *g = 255 * t;
      *b = 255 * p;
      break;
    case 1:
      // Yellow
      *r = 255 * q;
      *g = 255 * bright;
      *b = 255 * p;
      break;
    case 2:
      // Green
      *r = 255 * p;
      *g = 255 * bright;
      *b = 255 * t;
      break;
    case 3:
      // Cyan
      *r = 255 * p;
      *g = 255 * q;
      *b = 255 * bright ;
      break;
    case 4:
      // Blue
      *r = 255 * t;
      *g = 255 * p;
      *b = 255 * bright;
      break;
    case 5:
      // Magenta
      *r = 255 * bright;
      *g = 255 * p;
      *b = 255 * q;
      break;
  }

}


struct My_LED : Service::LightBulb { 

  int redPin;
  int greenPin;
  int bluePin;
  
  SpanCharacteristic *power;
  SpanCharacteristic *H;
  SpanCharacteristic *S;
  SpanCharacteristic *V;

  
  My_LED(int red, int green, int blue) : Service::LightBulb() {

    power=new Characteristic::On();
    H=new Characteristic::Hue(0);
    S=new Characteristic::Saturation(0);
    V=new Characteristic::Brightness(100);
    // V->setRange(5,100,1);

    this->redPin=red;
    this->greenPin=green;
    this->bluePin=blue;
    pinMode(redPin,OUTPUT);
    pinMode(greenPin,OUTPUT);
    pinMode(bluePin,OUTPUT);
    
  } 

  boolean update() {            

    // float h, s, v, r, g, b;
    float h, s, v;
    int r, g, b;
    bool powerSwitch;

    h=H->getVal<float>();
    s=S->getVal<float>();
    v=V->getVal<float>();
    powerSwitch=power->getVal();

    if (power->updated()) powerSwitch=power->getNewVal();
    if (H->updated()) h=H->getNewVal();
    if (S->updated()) s=S->getNewVal();
    if (V->updated()) v=V->getNewVal();

    if (powerSwitch) {
      myHSVtoRGB(h, s, v, &r, &g, &b);
      analogWrite(redPin, r);
      analogWrite(greenPin, g);
      analogWrite(bluePin, b);
    } else {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
    }
    return(true);
  
  } 
};