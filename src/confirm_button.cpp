// confirm_button.cpp
#include "confirm_button.h"
#include "config.h"

namespace {
  uint8_t gButtonPin = 0;

  bool gLastStable = HIGH;
  bool gLastRead   = HIGH;
  unsigned long gLastChangeMs = 0;
}

void button_init(uint8_t pin) {
  gButtonPin = pin;
  pinMode(gButtonPin, INPUT_PULLUP);

  gLastStable = digitalRead(gButtonPin);
  gLastRead   = gLastStable;
  gLastChangeMs = millis();
}

bool button_update() {
  bool reading = digitalRead(gButtonPin);

  if (reading != gLastRead) {
    gLastRead = reading;
    gLastChangeMs = millis();
  }

  if (millis() - gLastChangeMs > DEBOUNCE_MS) {
    if (reading != gLastStable) {
      gLastStable = reading;

      // Chỉ bắt cạnh nhấn (từ HIGH -> LOW)
      if (gLastStable == LOW) {
        return true;
      }
    }
  }
  return false;
}
