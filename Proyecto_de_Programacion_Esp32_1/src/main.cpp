//Programacion del primer Esp32 
//Tiene como objetivo captar  los datos y enviarlos a segundo esp32 
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h> //Protocolo de comunicación utilizado para la comunicación entre los dos ESP32
#include <DHT.h>

//definición del pin y tipo de sensor DHT
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Dirección MAC del receptor
uint8_t receiverMAC[] = {0x00, 0x4B, 0x12, 0x9B, 0x30, 0xC0};

// Estructura de datos a enviar
typedef struct struct_message {
  float temperature;
  float humidity;
} struct_message;

struct_message data;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Estado del envío: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Éxito" : "Fallo");
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error inicializando ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));   // Limpia la estructura
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;                     // Canal por defecto
  peerInfo.encrypt = false;                 // Sin encriptación

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Error al añadir el receptor");
    return;
  }
}

void loop() {
  data.humidity = dht.readHumidity();
  data.temperature = dht.readTemperature();

  if (isnan(data.humidity) || isnan(data.temperature)) {
    Serial.println("Error leyendo el DHT11");
    return;
  }

  esp_err_t result = esp_now_send(receiverMAC, (uint8_t *) &data, sizeof(data));

  if (result == ESP_OK) {
    Serial.println("Datos enviados correctamente");
  } else {
    Serial.println("Error al enviar los datos");
  }

  delay(2000);
}
