#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "CLARO1_377328";
const char *password = "1XG6YFIJ7R";
const char *urlSave = "https://catuses.com/proyecto/save.php";
const char *urlCheck = "https://catuses.com/proyecto/check_status.php"; // New endpoint for status check

#define boton 12
#define LED_BUILTIN 2

int a = 0;

void setup() {
  Serial.begin(115200);
  pinMode(boton, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int lectura = digitalRead(boton);
  if (lectura == LOW) {
    a = !a;
    delay(150);  // Debounce delay
    digitalWrite(LED_BUILTIN, a ? HIGH : LOW); // Control LED
    sendStatusToServer(a);  // Send status to the server when button pressed
  }
  delay(150);  // Debounce delay
  checkAndUpdateTable(); // Check status and update table if necessary
}

void sendStatusToServer(int status) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(urlSave) + "?status=" + String(status);

    http.begin(url);  // Specify destination for HTTP request
    int httpResponseCode = http.GET();  // Send the request

    if (httpResponseCode > 0) {
      String response = http.getString();  // Get the response
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error in HTTP request");
    }

    http.end();  // Free resources
  }
}

void checkAndUpdateTable() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(urlCheck); // Assuming urlCheck is the URL for checking the table status

    http.begin(url);  // Specify destination for HTTP request
    int httpResponseCode = http.GET();  // Send the request

    if (httpResponseCode > 0) {
      String response = http.getString();  // Get the response
      Serial.println("Table update response: " + response);

      // Parse the response to determine LED status
      int status = response.toInt(); // Convert the response to an integer

      if (status == 1) {
        digitalWrite(LED_BUILTIN, HIGH); // Turn LED ON
        Serial.println("LED is ON");
      } else if (status == 0) {
        digitalWrite(LED_BUILTIN, LOW); // Turn LED OFF
        Serial.println("LED is OFF");
      } else {
        Serial.println("Unexpected status received: " + response);
      }
    } else {
      Serial.println("Error in HTTP request");
    }

    http.end();  // Free resources
  }
}
