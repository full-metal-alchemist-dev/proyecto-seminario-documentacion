#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
//ESP32 GPIOs 30
const char* ssid = "CLARO_6d475a";
const char* password = "519b0515Dd";
String serverName = "https://moniraspyardu.000webhostapp.com/app/productos/04agregar.php";
const char* serverName2 = "http://moniraspyardu.000webhostapp.com/app/productos/02datav2.php?id=140&tabla=producto";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;
String sensorReadings;
String sensorReadingsArr[3];

void setup() {
  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      String serverPath = serverName + "?add=0&tabla=producto&descripcion=pruebadesdeurl&costo1=1&costo2=2";      
      http.begin(serverPath.c_str());      
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        sensorReadings = httpGETRequest(serverName2);
        Serial.println(sensorReadings);
        JSONVar myObject = JSON.parse(sensorReadings);

        if (JSON.typeof(myObject) == "undefined") {
          Serial.println("Parsing input failed!");
          return;
        }

        Serial.print("JSON object = ");
        Serial.println(myObject);
        JSONVar keys = myObject.keys();

        for (int i = 0; i < keys.length(); i++) {
          JSONVar value = myObject[keys[i]];
          Serial.print(keys[i]);
          Serial.print(" = ");
          Serial.println(value);
          sensorReadingsArr[i] = value;      
        }

        Serial.print("1 = ");
        Serial.println(sensorReadingsArr[0]);
        Serial.print("2 = ");
        Serial.println(sensorReadingsArr[1]);
        Serial.print("3 = ");
        Serial.println(sensorReadingsArr[2]);        
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }      
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }  
}



String httpGETRequest(const char* serverName2) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName2);  
  int httpResponseCode = http.GET();  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  
  http.end();
  return payload;

}
