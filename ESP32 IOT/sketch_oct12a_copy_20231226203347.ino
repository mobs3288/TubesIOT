#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 4      // DHT11 data pin is connected to GPIO 4
#define LDR_PIN 5     // LDR sensor digital output pin
#define RAIN_DO_PIN 21 // Raindrop sensor digital output pin

DHT dht(DHTPIN, DHT11);

unsigned long startTime = 0;
unsigned long totalSunshineTime = 0;
unsigned long totalRainTime = 0;

const char* ssid = "SSID";
const char* password = "Password";
const char* serverUrl = "http://Flask IP Address:5000/update_sensor_data"; // Change this URL to your server endpoint

void setup() {
  Serial.begin(115200);
  pinMode(LDR_PIN, INPUT);
  pinMode(RAIN_DO_PIN, INPUT);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  dht.begin();
}

void loop() {
  delay(2000);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Read raindrop sensor value (digital output)
  int rainValue = digitalRead(RAIN_DO_PIN);

  // If rain is not detected, start or continue the timer
  if (rainValue == 1) {
    if (startTime == 0) {
      // No rain detected, start the timer
      startTime = millis();
    } else {
      // No rain is still detected, calculate total rain time
      unsigned long currentTime = millis();
      totalRainTime = currentTime - startTime;
    }
  } else {
    // Rain is detected, reset the timer
    startTime = 0;
  }

  // Print the total rain time in seconds
  Serial.print("Total Rain Time (seconds): ");
  Serial.println(totalRainTime / 1000); // Convert milliseconds to seconds

  // Read light level from LDR sensor
  int lightLevel = digitalRead(LDR_PIN);

  // If light level is above the threshold (light condition), start or continue the timer
  if (lightLevel == 0) {
    if (startTime == 0) {
      // Light level just went above threshold, start the timer
      startTime = millis();
    } else {
      // Light level is still above threshold, calculate total sunshine time
      unsigned long currentTime = millis();
      totalSunshineTime = currentTime - startTime;
    }
  } else {
    // Light level is below the threshold (darkness), reset the timer
    startTime = 0;
  }

  // Print the total sunshine time in hours
  Serial.print("Total Sunshine Time (hours): ");
  Serial.println(totalSunshineTime / 3600000.0); // Convert milliseconds to hours

  Serial.println("Sending data to server...");

  HTTPClient http;

  // Send POST request
  http.begin(serverUrl);

  // Set content type to JSON
  http.addHeader("Content-Type", "application/json");

  // Create JSON payload
  String payload = "{\"temperature\":" + String(temperature) + ", \"humidity\":" + String(humidity) + ", \"rain_value\":" + String(rainValue) + ", \"sunshine_time\":" + String(totalSunshineTime / 3600000.0) + "}";

  // Send POST request
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("HTTP Request failed. Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(http.errorToString(httpResponseCode).c_str());
  }

  // Free resources
  http.end();
}
