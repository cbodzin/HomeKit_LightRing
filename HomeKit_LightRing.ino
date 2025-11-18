#include <HomeSpan.h> 
#include "My_LED.h"
#define LED_COUNT   16
#define LED_PIN     1



void setup() {

  Serial.begin(115200);
  homeSpan.begin(Category::Lighting,"CyCor LED");
  
  new SpanAccessory();   
  new Service::AccessoryInformation(); 
  new Characteristic::Identify();  
  new Characteristic::Manufacturer("CyCor");
  new Characteristic::Model("ESP32-RingLight");             
  new My_LED(LED_COUNT, LED_PIN);

} 

void loop(){
  
  // Just see if we have anything to do
  homeSpan.poll();
  
} 