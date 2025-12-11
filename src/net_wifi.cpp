#include "net_wifi.h"
#include "config.h"

#include <WiFi.h>

void wifi_connect() {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.println(F("Dang ket noi WiFi..."));
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }

  Serial.println();
  Serial.println(F("Da ket noi WiFi."));
  Serial.print(F("IP: "));
  Serial.println(WiFi.localIP());
}

void wifi_loop() {
  if (WiFi.status() != WL_CONNECTED) {
    wifi_connect();
  }
}
