#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

// MAC del ESP32 #1
uint8_t senderMAC[] = {0x00, 0x4B, 0x12, 0x9A, 0x14, 0x8C};

// Datos recibidos
typedef struct struct_message {
  float temperature;
  float humidity;
} struct_message;

struct_message incomingData;

// Comando LED
typedef struct command_message {
  char command;
} command_message;

command_message cmd;

// Recibe sensores
void OnDataRecv(const uint8_t * mac,
                const uint8_t *incomingDataBytes,
                int len) {

  memcpy(&incomingData,
         incomingDataBytes,
         sizeof(incomingData));

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

    Serial.println("Error inicializando ESP NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  esp_now_peer_info_t peerInfo;

  memset(&peerInfo, 0, sizeof(peerInfo));

  memcpy(peerInfo.peer_addr, senderMAC, 6);

  peerInfo.channel = 0;

  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {

    Serial.println("Error agregando peer");
    return;
  }

  Serial.println("Escribe C o N");
}

void loop() {

  // Leer serial
  if(Serial.available()){

    char dato = Serial.read();

    // Encender LED remoto
    if(dato == 'C'){

      cmd.command = 'C';

      esp_now_send(senderMAC,
                   (uint8_t *) &cmd,
                   sizeof(cmd));

      Serial.println("Comando ENCENDER enviado");
    }

    // Apagar LED remoto
    if(dato == 'N'){

      cmd.command = 'N';

      esp_now_send(senderMAC,
                   (uint8_t *) &cmd,
                   sizeof(cmd));

      Serial.println("Comando APAGAR enviado");
    }
  }
}