#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <DHT.h>

#define DHTPIN 13
#define DHTTYPE DHT11

#define LED_PIN 2

DHT dht(DHTPIN, DHTTYPE);

// MAC del receptor
uint8_t receiverMAC[] = {0x00, 0x4B, 0x12, 0x9B, 0x30, 0xC0};

// Datos sensores
typedef struct struct_message {
  float temperature;
  float humidity;
} struct_message;

struct_message data;

// Comando LED
typedef struct command_message {
  char command;
} command_message;

command_message cmd;

// Verifica envio
void OnDataSent(const uint8_t *mac_addr,
                esp_now_send_status_t status) {

  Serial.print("Estado envio: ");

  if(status == ESP_NOW_SEND_SUCCESS){
    Serial.println("OK");
  }
  else{
    Serial.println("Error");
  }
}

// Recibe comandos
void OnDataRecv(const uint8_t * mac,
                const uint8_t *incomingData,
                int len) {

  memcpy(&cmd, incomingData, sizeof(cmd));

  // C = encender
  if(cmd.command == 'C'){

    digitalWrite(LED_PIN, HIGH);

    Serial.println("LED ENCENDIDO");
  }

  // N = apagar
  if(cmd.command == 'N'){

    digitalWrite(LED_PIN, LOW);

    Serial.println("LED APAGADO");
  }
}

void setup() {

  Serial.begin(115200);

  dht.begin();

  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {

    Serial.println("Error inicializando ESP NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_register_recv_cb(OnDataRecv);

  esp_now_peer_info_t peerInfo;

  memset(&peerInfo, 0, sizeof(peerInfo));

  memcpy(peerInfo.peer_addr, receiverMAC, 6);

  peerInfo.channel = 0;

  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {

    Serial.println("Error agregando peer");
    return;
  }
}

void loop() {

  data.humidity = dht.readHumidity();

  data.temperature = dht.readTemperature();

  if (isnan(data.humidity) || isnan(data.temperature)) {

    Serial.println("Error leyendo DHT11");
    return;
  }

  esp_now_send(receiverMAC,
               (uint8_t *) &data,
               sizeof(data));

  delay(2000);
}