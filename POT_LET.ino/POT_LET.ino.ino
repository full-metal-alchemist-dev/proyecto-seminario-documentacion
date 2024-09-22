const int potPin = 34;  // Potentiometer connected to GPIO 34
const int ledPin = 16;  // LED connected to GPIO 16 (PWM pin)

// Variable for storing the potentiometer value
int potValue = 0;
int ledBrightness = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read the potentiometer value (0 to 4095)
  potValue = analogRead(potPin);

  // Map the potentiometer value to a PWM range (0 to 255)
  ledBrightness = map(potValue, 0, 4095, 0, 255);

  // Write the mapped brightness to the LED
  analogWrite(ledPin, ledBrightness);

  // Print the potentiometer and LED brightness values for debugging
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" | LED Brightness: ");
  Serial.println(ledBrightness);

  // Short delay to stabilize readings
  delay(100);
}
