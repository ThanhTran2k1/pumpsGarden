#include <Arduino.h>

#include <ESP8266WiFi.h>        // Include the Wi-Fi library

#include <NTPClient.h>

#include <WiFiUdp.h>


const char* ssid     = "P307";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "bayanhdeptrai";     // The password of the Wi-Fi network

int ledWifiStatus = D0;
int pumpPush = D1; 

unsigned long currentMillisWifi = 0;
unsigned long currentMillis = millis();
unsigned long led1Delay = 2000;
unsigned long led2Delay = 3000;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

bool onPumps = false;
int i=0;

void handlerPumps() {
  digitalWrite(pumpPush, LOW);
  delay(4000);
  Serial.print(++i);
  digitalWrite(pumpPush,HIGH);
}

String timeSet = "17:50";
String convert;
void handleTime() {
  String formattedTime = timeClient.getFormattedTime(); 
  String num = formattedTime.substring(0,5);
  Serial.println(num);
  if(num == timeSet) {
    Serial.println("YES");
  }else {
    Serial.println("NO");
  }
}

bool isConnected = false;
unsigned long previosTime = 0;
void setup() {
  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  pinMode(pumpPush, OUTPUT);
  timeClient.begin();
  timeClient.setTimeOffset(25200);
  
}

void loop() {
  timeClient.update();
  if(WiFi.status() == WL_CONNECTED && !isConnected) {
    Serial.println("Connected");
    isConnected = true;
  }
  if(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(ledWifiStatus, !digitalRead(ledWifiStatus));
    if(millis() - currentMillisWifi >= 1000) {
      currentMillisWifi = millis();
    }
    isConnected = false;
  }
  if(millis() - previosTime >= 1000) {
    previosTime = millis();
    handleTime();
  }
  
  
}