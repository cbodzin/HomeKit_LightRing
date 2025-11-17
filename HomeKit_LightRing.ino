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
  new My_LED(1,10,0);

} 

void loop(){
  
  // Just see if we have anything to do
  homeSpan.poll();
  
} 