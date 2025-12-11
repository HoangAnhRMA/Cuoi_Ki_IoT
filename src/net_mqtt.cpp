#include "net_mqtt.h"
#include "config.h"
#include "net_wifi.h"

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

WiFiClientSecure wifiClient;
PubSubClient mqtt(wifiClient);

static void mqttCallback(char *topic, byte *payload, unsigned int length) {
  Serial.print(F("MQTT message, topic: "));
  Serial.print(topic);
  Serial.print(F(" | payload: "));
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // Sau này anh xử lý logic điều khiển từ xa ở đây
}

void mqtt_connect() {
  wifiClient.setInsecure(); // demo: bỏ kiểm chứng CA

  mqtt.setServer(MQTT_BROKER, MQTT_PORT);
  mqtt.setCallback(mqttCallback);

  while (!mqtt.connected()) {
    wifi_loop(); // đảm bảo đang có WiFi

    Serial.print(F("Dang ket noi MQTT toi HiveMQ... "));

    String clientId = "esp32-medbox-";
    clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

    bool ok = mqtt.connect(clientId.c_str(), MQTT_USER, MQTT_PASS);
    if (ok) {
      Serial.println(F("THANH CONG"));
      mqtt.publish(TOPIC_TEST, "ESP32 connected!", true);
      // ví dụ subscribe sau này:
      // mqtt.subscribe("med/reminder/set");
    } else {
      Serial.print(F("THAT BAI, rc="));
      Serial.print(mqtt.state());
      Serial.println(F(" -> thu lai sau 5 giay"));
      delay(5000);
    }
  }
}

void mqtt_loop() {
  if (!mqtt.connected()) {
    mqtt_connect();
  }
  mqtt.loop();
}
