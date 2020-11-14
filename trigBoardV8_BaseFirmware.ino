#include "includes.h"

const char fwVersion[] = "excel-1.0";

void setup() {
  pinMode(ESPlatchPin, OUTPUT);
  digitalWrite(ESPlatchPin, HIGH);
  pinMode(LEDpin, OUTPUT);
  Serial.begin(115200);
  checkWakeupPins();
  loadConfiguration(filename, config);
  rtcInit(config.timerCountDown, false);
  Serial.println(getBattery(), 2);
  if (pushLogic()) { //decide if push will occur or not and what message will be
    if (wiFiNeeded) {
      if (connectWiFi()) {
        pushOver();
        pushSafer();
        ifttt();
        mqtt();
        webhook();
      }
    }
    udp();
  }

  killPower();
  waitForButton();
  initBluetooth();
}

void loop() {
  if (!OTAsetup)
    serviceBluetooth();
  else
    checkOTA();
}
