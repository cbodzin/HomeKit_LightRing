#include <HomeSpan.h> 
#include "My_LED.h"

void setup() {

  Serial.begin(115200);
  homeSpan.begin(Category::Lighting,"CyCor LED");
  
  new SpanAccessory();   
  new Service::AccessoryInformation(); 
  new Characteristic::Identify();  
  new Characteristic::Manufacturer("CyCor");
  new Characteristic::Model("ESP32-RingLight");             
  new My_LED(10);        // this instantiates a new LED Service.  Where is this defined?  What happpened to Characteristic::On?  Keep reading...

} 

void loop(){
  
  homeSpan.poll();
  
} 