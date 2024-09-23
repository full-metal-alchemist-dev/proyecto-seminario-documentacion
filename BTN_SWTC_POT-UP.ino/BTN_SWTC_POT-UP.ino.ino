#include <WiFi.h>
#include <HTTPClient.h>

// Wi-Fi credentials
const char *ssid = "CLARO1_377328";
const char *password = "1XG6YFIJ7R";

// Define environment (1 for production, 0 for development)
#define ENV_PRODUCTION 0

// Server names based on environment
#if ENV_PRODUCTION
  const char *serverName = "https://catuses.com/proyecto";  // Production URL
#else
  const char *serverName = "http://192.168.1.150/proyecto";  // Development URL
#endif

// Endpoints
const char *urlSave = "/save.php";
const char *urlCheck = "/check_status.php";
const char *urlSavePotentiometer = "/save_potentiometer.php";

#define boton 12
#define LED_BUILTIN 2
const int potPin = 34;  // Potentiometer pin
const int ledPin = 16;  // LED PWM pin

int buttonStatus = 0;
int potValue = 0;
int ledBrightness = 0;
int lastPotValue = -1;  // To track potentiometer changes

void setup() {
  Serial.begin(115200);
  pinMode(boton, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);  // Set PWM pin for LED

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  handleButton();
  checkAndUpdateTable();
  delay(150);  // For debounce
}

// Handle button press and send status to server
void handleButton() {
  if (digitalRead(boton) == LOW) {
    buttonStatus = !buttonStatus;
    delay(150);  // Debounce delay
    digitalWrite(LED_BUILTIN, buttonStatus ? HIGH : LOW);
    sendDataToServer(urlSave, "status", buttonStatus);
  }
}

// Check server status and update LED
void checkAndUpdateTable() {
  String response = getDataFromServer(urlCheck);
  int status = response.toInt();  // Convert response to integer
  
  if (status == 1) {
    digitalWrite(LED_BUILTIN, HIGH);  // Turn LED ON
    updatePotentiometerData();        // Adjust LED brightness based on potentiometer
  } else {
    digitalWrite(LED_BUILTIN, LOW);   // Turn LED OFF
    analogWrite(ledPin, 0);           // Set PWM brightness to 0
  }
  delay(150);
}

// Update potentiometer data and send it to the server
void updatePotentiometerData() {
  potValue = analogRead(potPin);  // Read potentiometer value

  if (potValue != lastPotValue) {
    lastPotValue = potValue;
    ledBrightness = map(potValue, 0, 4095, 0, 255);  // Map to PWM range
    analogWrite(ledPin, ledBrightness);              // Set LED brightness
    sendDataToServer(urlSavePotentiometer, "potValue", ledBrightness);  // Send to server
  }
}

// Function to send data to the server
void sendDataToServer(const char* endpoint, const char* param, int value) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverName) + String(endpoint) + "?" + String(param) + "=" + String(value);

    http.begin(url);  // Specify destination
    int httpResponseCode = http.GET();  // Send the request

    if (httpResponseCode > 0) {
      String response = http.getString();  // Get the response
      Serial.println("Server response: " + response);
    } else {
      Serial.println("Error in HTTP request");
    }

    http.end();  // Free resources
  }
}

// Function to get data from the server
String getDataFromServer(const char* endpoint) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverName) + String(endpoint);

    http.begin(url);  // Specify destination
    int httpResponseCode = http.GET();  // Send the request
    String response = "";

    if (httpResponseCode > 0) {
      response = http.getString();  // Get the response
      Serial.println("Server response: " + response);
    } else {
      Serial.println("Error in HTTP request");
    }

    http.end();  // Free resources
    return response;
  }
  return "";
}
