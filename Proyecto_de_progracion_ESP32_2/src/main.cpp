#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

// Dirección MAC del emisor
uint8_t senderMAC[] = {0x00, 0x4B, 0x12, 0x9A, 0x14, 0x8C};

// Estructura de datos recibidos
typedef struct struct_message {
  float temperature;
  float humidity;
} struct_message;

struct_message incomingData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingDataBytes, int len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));
  Serial.print("Temperatura: ");
  Serial.print(incomingData.temperature);
  Serial.print(" °C | Humedad: ");
  Serial.print(incomingData.humidity);
  Serial.println(" %");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error inicializando ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));   // Limpia la estructura
  memcpy(peerInfo.peer_addr, senderMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Error al añadir el emisor");
    return;
  }
}

void loop() {
  // El receptor solo espera datos
}