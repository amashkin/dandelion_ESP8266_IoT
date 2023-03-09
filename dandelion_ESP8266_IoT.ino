#include "danLogic.h"
#include "danCloud.h"
#include "danOTA.h"

void setup() {
  Serial.begin(115200);
  delay(5000);

  danLogicSetup(); // danLogic.h 
  
  OTA_init();  // danOTA.h Over The Air
  
  initProperties();                                  // Part of ArduinoCloud. Defined in danCloud.h
  ArduinoCloud.begin(ArduinoIoTPreferredConnection); // Connect to Arduino IoT Cloud

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  ArduinoOTA.handle();
  danLogicHandle();
}