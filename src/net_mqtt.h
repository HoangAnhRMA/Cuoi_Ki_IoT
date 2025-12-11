#pragma once
#include <PubSubClient.h>

// Cho module khác dùng chung client MQTT
extern PubSubClient mqtt;

// Kết nối MQTT (gọi trong setup)
void mqtt_connect();

// Gọi định kỳ trong loop
void mqtt_loop();
