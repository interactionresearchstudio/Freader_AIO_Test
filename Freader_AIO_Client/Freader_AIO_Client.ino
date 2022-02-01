#include <espnow.h>
#include <ESP8266WiFi.h>

uint8_t globalMac[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct message_struct {
  uint8_t rfid[4];
} message_struct;

message_struct msg;

#define LED_BUILTIN 2

void onSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.println("Status:");
  Serial.println(sendStatus);
}

void setup() {
  WiFi.mode(WIFI_STA);
  
  Serial.begin(115200);
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(globalMac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  esp_now_register_send_cb(onSent);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  sendTag(random(0, 255), random(0, 255), random(0, 255), random(0, 255));
  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(10000);
}

void sendTag(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
  msg.rfid[0] = a;
  msg.rfid[1] = b;
  msg.rfid[2] = c;
  msg.rfid[3] = d;

  Serial.print("Sending ");
  Serial.print(msg.rfid[0], HEX);
  Serial.print(msg.rfid[1], HEX);
  Serial.print(msg.rfid[2], HEX);
  Serial.println(msg.rfid[3], HEX);
  esp_now_send(NULL, (uint8_t *) &msg, sizeof(msg));
}
