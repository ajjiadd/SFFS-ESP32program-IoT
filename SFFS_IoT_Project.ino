
// SFFS - Smart Fish Feading System

#define BLYNK_TEMPLATE_ID "TMPL66oRUJVkd"
#define BLYNK_TEMPLATE_NAME "SFFS Project"
#define BLYNK_AUTH_TOKEN "cCVBzGw1d2IJmjAJb5YNoR3gW3dl5JAV"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// WiFi & Blynk Credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "POCO M3"; 
char pass[] = "jiadjiad0"; 

// Hardware Pins
#define WATER_SENSOR_PIN 32  //(GPIO32)
#define PUMP_PIN 25          //(GPIO25)
#define SERVO1_PIN 2         //(GPIO2)
#define THRESHOLD 30         //(30%)

Servo servo1; // Servo

void setup() {
  Serial.begin(115200);
  
  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);
  
  // Initialize servo motor
  servo1.attach(SERVO1_PIN); 
  
  // Pump system setup
  pinMode(WATER_SENSOR_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW); 
}

void loop() {
  Blynk.run(); 
  
  // water level
  int sensorValue = analogRead(WATER_SENSOR_PIN);
  float waterLevel = (sensorValue / 4095.0) * 100;
  
  
  Blynk.virtualWrite(V2, waterLevel); 
  
  
  if (waterLevel > THRESHOLD) {
    digitalWrite(PUMP_PIN, HIGH);
    Blynk.virtualWrite(V3, "PUMP: OFF"); 
  } else {
    digitalWrite(PUMP_PIN, LOW);
    Blynk.virtualWrite(V3, "PUMP: ON");
  }
  
  delay(1000); 
}

// Control servo (V0)
BLYNK_WRITE(V0) { 
  int angle = param.asInt(); 
  servo1.write(angle); 
  Blynk.virtualWrite(V1, angle); 
}