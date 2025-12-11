#pragma once
#include <Arduino.h>

constexpr auto WIFI_SSID = "TP-Link_ACDA";
constexpr auto WIFI_PASS = "20653880";

constexpr auto MQTT_BROKER = "ab481f25d392452bb38df3df6cf0b4ef.s1.eu.hivemq.cloud";
constexpr uint16_t MQTT_PORT = 8883;

constexpr auto MQTT_USER = "HoangAnh";
constexpr auto MQTT_PASS = "HoangLong@321";

constexpr auto TOPIC_TEST    = "med/test";
constexpr auto TOPIC_DOOR    = "med/box/door";
constexpr auto TOPIC_CONFIRM = "med/box/confirm";
constexpr auto TOPIC_DOSE    = "med/box/doseCount";

constexpr uint8_t PIN_REED   = 4;   
constexpr uint8_t PIN_BUTTON = 5;  
constexpr uint8_t PIN_LED    = 16; 
constexpr uint8_t PIN_BUZZER = 18; 

constexpr unsigned long DEBOUNCE_MS       = 50;
constexpr unsigned long REMINDER_DELAY_MS = 10000; 

constexpr bool BUZZER_ACTIVE_LOW = false;
