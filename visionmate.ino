/*
 * VisionMate — IoT-Based Smart Assistive Mobility Stick
 * 
 * Final Year B.Tech Project
 * Department of Electronics & Communication Engineering
 * Sreenidhi Institute of Science and Technology, Hyderabad (2025)
 * 
 * Authors: Kolli Hema Sri Sruthi, Shreya Jha, G. Vyshnavi
 * 
 * Hardware:
 *   - ESP32 Microcontroller
 *   - HC-SR04 Ultrasonic Sensor (obstacle detection)
 *   - MQ6 Gas Sensor (smoke detection)
 *   - Moisture Sensor 12V + Relay (wet surface detection)
 *   - uBlox Neo-M8N GPS Module (location tracking)
 *   - Piezoelectric Buzzer (local alert)
 *   - L298N Motor Driver Module
 * 
 * Features:
 *   - Real-time obstacle detection with buzzer + Bluetooth alert
 *   - Wet surface detection and warning
 *   - Smoke/gas detection and warning
 *   - Live GPS tracking via ThingSpeak IoT platform
 *   - Bluetooth audio/text feedback via mobile app
 */

#include "BluetoothSerial.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPS++.h>

// ─────────────────────────────────────────
// WiFi & ThingSpeak Configuration
// Replace with your own credentials before uploading
// ─────────────────────────────────────────
const char* ssid             = "YOUR_WIFI_SSID";       // Replace with your WiFi name
const char* password         = "YOUR_WIFI_PASSWORD";   // Replace with your WiFi password
const char* thinkSpeakApiKey = "YOUR_THINGSPEAK_API_KEY"; // Replace with your ThingSpeak Write API Key
const char* thinkSpeakServer = "http://api.thingspeak.com/update";

// ─────────────────────────────────────────
// Pin Definitions
// ─────────────────────────────────────────
const int trigFront   = 5;    // HC-SR04 Trigger pin
const int echoFront   = 18;   // HC-SR04 Echo pin
const int soilSensor  = 34;   // Moisture sensor analog pin
const int smokeSensor = 35;   // MQ6 gas sensor analog pin
const int buzzer      = 19;   // Piezoelectric buzzer pin

// ─────────────────────────────────────────
// Sensor Thresholds
// ─────────────────────────────────────────
const int OBSTACLE_THRESHOLD = 50;   // cm — trigger alert if object closer than this
const int MOISTURE_THRESHOLD = 30;   // % — trigger alert if moisture above this
const int SMOKE_THRESHOLD    = 1000; // ADC units — empirically calibrated during testing

// ─────────────────────────────────────────
// Object Initialisation
// ─────────────────────────────────────────
BluetoothSerial BT;
TinyGPSPlus gps;
#define gpsSerial Serial2

// ─────────────────────────────────────────
// Utility: Measure distance via ultrasonic sensor
// Returns distance in cm, or -1 if no object detected within range
// ─────────────────────────────────────────
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 50000); // 50ms timeout
  return (duration == 0) ? -1 : duration * 0.034 / 2;
}

// ─────────────────────────────────────────
// Utility: Send sensor data to ThingSpeak
// Fields: field1=moisture, field2=smoke, field3=distance,
//         field4=latitude, field5=longitude
// ─────────────────────────────────────────
void sendDataToThinkSpeak(int moisture, int smoke, long distance, float lat, float lng) {
  if (WiFi.status() != WL_CONNECTED) return;

  char url[200];
  sprintf(url,
    "%s?api_key=%s&field1=%d&field2=%d&field3=%ld&field4=%.6f&field5=%.6f",
    thinkSpeakServer, thinkSpeakApiKey, moisture, smoke, distance, lat, lng
  );

  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  Serial.printf("ThingSpeak Response: %d\n", httpResponseCode);
  http.end();
}

// ─────────────────────────────────────────
// Setup
// ─────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  BT.begin("ESP32_Sensor_Monitor");        // Bluetooth device name
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17); // GPS on UART2 (RX=16, TX=17)

  // Configure pins
  pinMode(trigFront,   OUTPUT);
  pinMode(echoFront,   INPUT);
  pinMode(buzzer,      OUTPUT);
  pinMode(soilSensor,  INPUT);
  pinMode(smokeSensor, INPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

// ─────────────────────────────────────────
// Main Loop
// ─────────────────────────────────────────
void loop() {
  // Read all sensors
  long distanceFront   = getDistance(trigFront, echoFront);
  int  soilValue       = analogRead(soilSensor);
  int  smokeValue      = analogRead(smokeSensor);
  int  moisturePercent = map(soilValue, 0, 4095, 100, 0); // Invert: 0=wet, 4095=dry

  // Parse GPS data
  float latitude = 0.0, longitude = 0.0;
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }
  if (gps.location.isValid()) {
    latitude  = gps.location.lat();
    longitude = gps.location.lng();
  }

  // Send all readings to ThingSpeak
  sendDataToThinkSpeak(moisturePercent, smokeValue, distanceFront, latitude, longitude);

  // ── Alert Logic (priority: obstacle > water > smoke > normal) ──
  if (distanceFront != -1 && distanceFront < OBSTACLE_THRESHOLD) {
    // Obstacle detected
    digitalWrite(buzzer, HIGH);
    BT.printf("⚠ Obstacle: %ld cm\n", distanceFront);

  } else if (moisturePercent > MOISTURE_THRESHOLD) {
    // Wet surface detected
    digitalWrite(buzzer, HIGH);
    BT.printf("⚠ Water detected: %d%%\n", moisturePercent);

  } else if (smokeValue > SMOKE_THRESHOLD) {
    // Smoke/gas detected
    digitalWrite(buzzer, HIGH);
    BT.printf("⚠ Smoke detected: %d\n", smokeValue);

  } else {
    // All clear
    digitalWrite(buzzer, LOW);
    BT.println("All readings normal.");
  }

  delay(5000); // Wait 5 seconds before next reading cycle
}
