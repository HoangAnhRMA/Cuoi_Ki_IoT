#include "reed_sensor.h"
#include "config.h"  

namespace {
  uint8_t gReedPin = 4;

  bool gLastStable = HIGH;
  bool gLastRead   = HIGH;
  unsigned long gLastChangeMs = 0;
}

void reed_init(uint8_t pin) {
  gReedPin = pin;
  pinMode(gReedPin, INPUT_PULLUP);

  gLastStable = digitalRead(gReedPin);
  gLastRead   = gLastStable;
  gLastChangeMs = millis();
}

bool reed_update() {
  bool reading = digitalRead(gReedPin);

  if (reading != gLastRead) {
    gLastRead = reading;
    gLastChangeMs = millis();
  }

  if (millis() - gLastChangeMs > DEBOUNCE_MS) {
    if (reading != gLastStable) {
      gLastStable = reading;
      return true;  
    }
  }
  return false;
}

bool reed_isOpen() {

  return (gLastStable == HIGH);
}
