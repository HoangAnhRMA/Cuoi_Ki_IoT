#pragma once
#include <PubSubClient.h>

extern PubSubClient mqtt;

void mqtt_connect();

void mqtt_loop();
