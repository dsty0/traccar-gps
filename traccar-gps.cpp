#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* traccar_server = "http://traccar.your-domain.com:80";
const char* device_id = "your-device-id";

float dummy_lat = -7.7532461;
float dummy_lon = 110.33184;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void sendToTraccar(float lat, float lon) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(traccar_server) + "/?id=" + device_id + "&lat=" + String(lat, 6) + "&lon=" + String(lon, 6);
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.printf("HTTP Response code: %d\n", httpCode);
    } else {
      Serial.printf("HTTP GET failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

void loop() {
  sendToTraccar(dummy_lat, dummy_lon);

  dummy_lat += 0.0100;
  dummy_lon += 0.0100;

  delay(10000); 
}
