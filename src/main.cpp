#include <Arduino.h>
#include <WiFi.h>
#include <credentials.h>
#include <HTTPClient.h>


const char* ssid     = WIFINAME;
const char* password = WIFIPASS;
bool error = false;

int LED_BUILTIN = 2;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  //=========================================
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("WiFi connected");
  digitalWrite(LED_BUILTIN, LOW);
  //=========================================
}

void loop() {
  // put your main code here, to run repeatedly:
  //Send an HTTP POST request every 10 minutes
    //Check WiFi connection status
    if(error) {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
    if(WiFi.status()== WL_CONNECTED){
        HTTPClient http;

        String serverPath = "http://192.168.1.194/";
        
        // Your Domain name with URL path or IP address with path
        http.begin(serverPath.c_str());
        
        // Send HTTP GET request
        int httpResponseCode = http.GET();
        
        if (httpResponseCode>0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = http.getString();
          Serial.println(payload);
        }
        else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();
      }
      else {
        Serial.println("Request unsuccessful.");
        error = true;
      }
      delay(500);
    }
}