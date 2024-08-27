#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "CLARO1_377328";
const char *password = "1XG6YFIJ7R";
const char *urlTest = "http://192.168.1.150/appweb/test/test.php?id=1&tabla=test";



void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.print("ESP32 Dev Modulo, Conectando con tu Red Wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("");
  Serial.print("Conectado. direccion IP asignada a tu Modulo: ");
  Serial.println(WiFi.localIP());

  String jsonResponse = httpGETRequestTest(urlTest);

  DynamicJsonDocument doc(1024); 
  DeserializationError error = deserializeJson(doc, jsonResponse);

  if (error) {
    Serial.print("Error al Parsear en formato JSON: ");
    Serial.println(error.c_str());
    return;
  }

  // Extract and print the JSON fields
  Serial.println("");
  Serial.println("Prueba comunicacion con el servidor:");
  Serial.println("");
  Serial.println("Respuesta del Servidor (formato json):");
  Serial.println("");
  Serial.print("ID: ");
  Serial.println(doc["id"].as<String>());
  Serial.print("Descripcion: ");
  Serial.println(doc["descripcion"].as<String>());
  Serial.print("Dato1: ");
  Serial.println(doc["dato1"].as<String>());
  Serial.print("Dato2: ");
  Serial.println(doc["dato2"].as<String>());
  Serial.print("Estado Registro: ");
  Serial.println(doc["estado_registro"].as<String>());
}

void loop() {}

String httpGETRequestTest(const char *urlTest){
  WiFiClient client;
  HTTPClient http;
  http.begin(client, urlTest);
  int httpResponseCode = http.GET();
  String payload = "{}";
  if (httpResponseCode > 0)  {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}
