#include <Arduino.h>
#include "config.h"
#include "net_wifi.h"
#include "net_mqtt.h"
#include "med_box.h"

void setup() {
  Serial.begin(9600);
  delay(200);

  wifi_connect();
  mqtt_connect();
  med_setup();
}

void loop() {
  wifi_loop();
  mqtt_loop();
  med_loop();
  delay(5);
}
