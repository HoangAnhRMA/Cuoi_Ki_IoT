#pragma once
#include <Arduino.h>

void reed_init(uint8_t pin);

bool reed_update();

bool reed_isOpen();
