// confirm_button.h
#pragma once
#include <Arduino.h>

// Khởi tạo nút nhấn với chân tương ứng (INPUT_PULLUP)
void button_init(uint8_t pin);

// Gọi thường xuyên trong loop.
// Trả về true *một lần* mỗi khi phát hiện nhấn (LOW) ổn định.
bool button_update();
