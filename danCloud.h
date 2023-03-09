#ifndef __DANCLOUD_H_
#define __DANCLOUD_H_
// DO NOT EDIT const and function's names = they are related to ArdouinoCloud.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "danLogic.h"
void danLogicSwitch01Changed(bool bSwitch); // Declared in danLogic.h
void danLogicSwitch02Changed(bool bSwitch); // Declared in danLogic.h

#define DEVENV
//#define PRODENV

#ifdef PRODENV
  const char DEVICE_LOGIN_NAME[]  = "95a1c895-884e-4467-8088-360a6ec8f577"; // PROD
  const char DEVICE_KEY[]  = "GPLKRBRHJ2PV2ZONLVH4";                        // PROD
#else
  const char DEVICE_LOGIN_NAME[] = "083aba52-a166-40e8-b3fe-1cc871d39316";  // DEV
  const char DEVICE_KEY[] = "PEQV0ZUIL4RDWCTT1I5Z";                         // DEV
#endif

const char SSID[] = "TP-Link_1160";  // Network SSID (name)
const char PASS[] = "41985465";      // Network password (use for WPA, or use as key for WEP)

void onChangeSwitch01();
void onChangeSwitch02();
void setSwitch01(bool b);
void setSwitch02(bool b);

bool bSwitch_01 = false; // Fan switcher
bool bSwitch_02 = false; // Water pump swithcher
String sStatus;

void initProperties(){
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(bSwitch_01, READWRITE, ON_CHANGE, onChangeSwitch01);
  ArduinoCloud.addProperty(bSwitch_02, READWRITE, ON_CHANGE, onChangeSwitch02); 
  ArduinoCloud.addProperty(sStatus, READ, SECONDS, NULL);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

// Fan == Switch 01 has been changed
void onChangeSwitch01() {
  Serial.print("danCloud:: Switch 01 has new value: ");
  Serial.println(bSwitch_01);

  danLogicSwitch01Changed(bSwitch_01);
}

// Water pump == Switch 02 has been changed
void onChangeSwitch02() {
  Serial.print("danCloud:: Switch 02 has new value: ");
  Serial.println(bSwitch_02);

  danLogicSwitch02Changed(bSwitch_02);
}

void setSwitch01(bool b) {
  bSwitch_01 = b;
}

void setSwitch02(bool b) {
  bSwitch_02 = b;
}

#endif 