#pragma once
#include <Arduino.h>

// ========== WiFi ==========
constexpr auto WIFI_SSID = "TP-Link_ACDA";
constexpr auto WIFI_PASS = "20653880";

// ========== MQTT (HiveMQ Cloud) ==========
constexpr auto MQTT_BROKER = "ab481f25d392452bb38df3df6cf0b4ef.s1.eu.hivemq.cloud";
constexpr uint16_t MQTT_PORT = 8883;

constexpr auto MQTT_USER = "HoangAnh";
constexpr auto MQTT_PASS = "HoangLong@321";

// ========== MQTT TOPIC ==========
constexpr auto TOPIC_TEST    = "med/test";
constexpr auto TOPIC_DOOR    = "med/box/door";
constexpr auto TOPIC_CONFIRM = "med/box/confirm";
constexpr auto TOPIC_DOSE    = "med/box/doseCount";

// ========== CHÂN PHẦN CỨNG ==========
constexpr uint8_t PIN_REED   = 4;   // công tắc từ
constexpr uint8_t PIN_BUTTON = 5;   // nút xác nhận
constexpr uint8_t PIN_LED    = 16;  // LED
constexpr uint8_t PIN_BUZZER = 18;  // buzzer

// ========== THAM SỐ THỜI GIAN ==========
constexpr unsigned long DEBOUNCE_MS       = 50;
constexpr unsigned long REMINDER_DELAY_MS = 10000; // 10s

// Buzzer active LOW?
constexpr bool BUZZER_ACTIVE_LOW = false;
