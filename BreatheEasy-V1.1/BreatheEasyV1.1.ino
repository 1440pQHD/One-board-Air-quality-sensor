//BreatheEasy code V1.0
// Basic sensor reading from a DHT11 (temporary) and website hosting on local network alongside status LED
#include <DHT.h>
#include <WebServer.h>
#include <WiFi.h>
#include "index.h"

#define DHTPIN 14
#define DHTTYPE DHT11

#define MQ3_PIN 34
#define MQ3_WARMUP 60000UL

const float TEMP_HIGH = 40.0;
const float TEMP_LOW = 5.0;

const float HUM_HIGH = 90.0;
const float HUM_LOW = 20.0;

const int MQ3_HIGH = 2200;

const char* ssid = "Wifi";
const char* password = "12345678";

unsigned long bootTime;

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

//Below, the website code has been placed


String latestEvent = "System started.";
String eventLevel = "Info";
bool alarmActive = false;

String formatUptime() {
  unsigned long seconds = millis() / 1000;
  int hours = seconds / 3600;
  seconds %= 3600;
  int minutes = seconds / 60;
  seconds %= 60;

  char buffer[20];
  sprintf(buffer, "%02d:%02d:%02lu", hours, minutes, seconds);
  return String(buffer);
}

String getTimeString(){
  unsigned long seconds = millis() / 1000;
  int hours = (seconds / 3600) % 24;
  int minutes = (seconds / 60) % 60;
  int secs = seconds % 60;

  char buffer[10];
  sprintf(buffer, "%02d:%02d:%02d", hours, minutes, secs);
  return String(buffer);
}

// JSON API
void handleData(){
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int mqADC = analogRead(MQ3_PIN);

  bool mqReady = (millis() - bootTime) >= MQ3_WARMUP;
  int remaining = 0;

  if(!mqReady){
    remaining = (MQ3_WARMUP - (millis() - bootTime)) / 1000;
  }

  alarmActive = false;

  //Checking the Temp
  if(!isnan(temperature)){
    if(temperature > TEMP_HIGH){
      latestEvent = "High temperature detected";
      eventLevel = "Warning";
      alarmActive = true;
    }
    if(temperature < TEMP_LOW){
      latestEvent = "Low temperature detected";
      eventLevel = "Warning";
      alarmActive = true;
    }
  }

  //Checking Humidity
  if(!isnan(humidity)){
    if(humidity > HUM_HIGH){
      latestEvent = "High humidity detected";
      eventLevel = "Warning";
      alarmActive = true;
    }
    if(humidity < HUM_LOW){
      latestEvent = "Low humidity detected";
      eventLevel = "Warning";
      alarmActive = true;
    }
  }

  if(mqReady){
    if(mqADC > MQ3_HIGH){
      latestEvent = "MQ-3 Alcohol threshold exceeded";
      eventLevel = "Alert";
      alarmActive = true;
    }
  }
  
  if(!alarmActive && mqReady && !isnan(temperature) && !isnan(humidity)){
    latestEvent = "System operating nominally";
    eventLevel = "Info";
  }

  String json = "{";
  json += "\"temperature\":";
  json += isnan(temperature) ? "null" : String(temperature, 1);
  json += ",\"humidity\":";
  json += isnan(humidity) ? "null" : String(humidity, 1);
  json += ",\"mq\":";
  json += String(mqADC);
  json += ",\"mqReady\":";
  json += mqReady ? "true" : "false";
  json += ",\"remaining\":";
  json += String(remaining);
  json += ",\"alarm\":";
  json += alarmActive ? "true" : "false";
  json += ",\"event\":\"";
  json += latestEvent;
  json += "\",\"level\":\"";
  json += eventLevel;
  json += "\",\"uptime\":\"";
  json += formatUptime();
  json += "\",\"time\":\"";
  json += getTimeString();
  json += "\"}";

  server.send(200, "application/json", json);
}

void handleRoot() {
  server.send(200, "text/html", webpage);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Webserver...");
  bootTime = millis();
  
  WiFi.begin(ssid, password);
  dht.begin();
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
  
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 1000) {
    lastPrint = millis();
    
    // Prints: Temperature, Humidity, MQ-3
    Serial.print(dht.readTemperature(), 1);
    Serial.print(", ");
    Serial.print(dht.readHumidity(), 1);
    Serial.print(", ");
    Serial.println(analogRead(MQ3_PIN));
  }
}
