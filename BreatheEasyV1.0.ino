

//BreatheEasy code V1.0
// Basic sensor reading from a DHT11 (temporary) and website hosting on local network alongside status LED
#include <DHT.h>
#include <WebServer.h>
#include <WiFi.h>


#define DHTPIN 14
#define LEDPIN 26
#define DHTTYPE DHT11

const char* ssid = "Wifi";
const char* password = "12345678";


DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void handleRoot() {

  float humidity = dht.readHumidity(); //Reading of the humidity
  float temperature = dht.readTemperature();//Reading of the temperature

  String html = "<!DOCTYPE html><html>";
  html += "<head>";
  html += "<meta http-equiv='refresh' content='5'>";
  html +="<title>BreatheEasy - Preventing invisible hazards</title>";
  html += "</head>";
  html += "<body style='font-family=Arial;text-allign:cemter;'>";
  html += "<img src='https://i.postimg.cc/j2DFTRGy/image.png' width='150'> <br>";
  html += "<h1>BreatheEasy Enviroment monitor</h1>";

  if (isnan(temperature) || isnan(humidity)) {
    html += "<p>Sensor Error</p>";
  } else {
    html += "<h2>Temperature</h2>";
    html += "<p>";
    html += String(temperature);
    html += " &deg;C</p>";

    html += "<h2>Humidity</h2>";
    html += "<p>";
    html += String(humidity);
    html += " %</p>";
  }

  html += "</body></html>";

  server.send(200, "text/html", html);



}

void setup() {
  Serial.begin(115200);
  Serial.print("Starting Webserver...");
  WiFi.begin(ssid, password);
  dht.begin();
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print(WiFi.localIP());
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
