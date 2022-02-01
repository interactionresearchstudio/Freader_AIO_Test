#include <espnow.h>
#include <ESP8266WiFi.h>

uint8_t globalMac[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct message_struct {
  uint8_t rfid[4];
} message_struct;

message_struct msg;

void setup() {
  Serial.begin(115200);
  if (esp_now_init() == ERR_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(globalMac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  sendTag(random(0, 255), random(0, 255), random(0, 255), random(0, 255));
  delay(10000);
}

void sendTag(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
  uint8_t macAddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  msg.rfid[0] = a;
  msg.rfid[1] = b;
  msg.rfid[2] = c;
  msg.rfid[3] = d;
  esp_now_send(macAddr, (uint8_t *) &msg, sizeof(msg));
}
