#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// TagoIO
const char* tago_host = "https://api.tago.io/data";
const char* tago_token = "3ffe4c7d-09a6-4b41-9788-189a0991c893";

// DHT22
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Sensor ultrassônico
#define TRIG_PIN 5
#define ECHO_PIN 18

// limites
const float LIMIAR_UMIDADE_ALTA = 60.0;
const float ALTURA_RECIPIENTE_MM = 2000.0;
const float LIMITE_AGUA_MM = 1500.0;

void conectarWiFi() {
  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password, 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" conectado!");
}

float medirNivelAguaMM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);
  float distanciaMM = duracao * 0.0343 / 2.0 * 10.0;
  float nivelAgua = ALTURA_RECIPIENTE_MM - distanciaMM;
  if (nivelAgua < 0) nivelAgua = 0;
  Serial.println(nivelAgua);
  return nivelAgua;
}

void enviarParaTago(float umidade, float nivelAgua, JsonArray alertas) {
  WiFiClientSecure client;
  client.setInsecure();  
  HTTPClient https;
  https.begin(client, tago_host);
  https.addHeader("Content-Type", "application/json");
  https.addHeader("Device-Token", tago_token);

  StaticJsonDocument<512> doc;
  JsonArray data = doc.to<JsonArray>();

  JsonObject umidObj = data.createNestedObject();
  umidObj["variable"] = "umidade";
  umidObj["value"] = round(umidade); 

  JsonObject nivelObj = data.createNestedObject();
  nivelObj["variable"] = "nivel_agua";
  nivelObj["value"] = round(nivelAgua);  


  for (JsonVariant alerta : alertas) {
    JsonObject alertObj = data.createNestedObject();
    alertObj["variable"] = "alerta";
    alertObj["value"] = alerta.as<String>();
  }

  String jsonStr;
  serializeJson(doc, jsonStr);

  int httpCode = https.POST(jsonStr);
  String response = https.getString();

  Serial.print("HTTP Status: ");
  Serial.println(httpCode);
  Serial.print("Resposta: ");
  Serial.println(response);

  https.end();
}

void setup() {
  Serial.begin(115200);
  conectarWiFi();
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  float umidadeAr = dht.readHumidity();
  float nivelAguaMM = medirNivelAguaMM();

  if (isnan(umidadeAr)) {
    Serial.println("Erro na leitura do DHT22");
    return;
  }
  StaticJsonDocument<128> alertaDoc;
  JsonArray alertas = alertaDoc.to<JsonArray>();
 alertas.add("-");
  if (umidadeAr > LIMIAR_UMIDADE_ALTA && nivelAguaMM > LIMITE_AGUA_MM) {
  alertas.add("ALERTA CRITICO - ALTO NÍVEL DE ALAGAMENTO");
} 
  else {
    if (umidadeAr > LIMIAR_UMIDADE_ALTA) {
      alertas.add("Umidade do ar Alta");
      Serial.println(umidadeAr);
  }
    if (nivelAguaMM > LIMITE_AGUA_MM) {
      alertas.add("NÍVEL DA ÁGUA CRÍTICO");
      Serial.println(nivelAguaMM);
  }
}

  // Envia
  enviarParaTago(umidadeAr, nivelAguaMM, alertas);

  delay(5000);
}