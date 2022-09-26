#include <Arduino.h>

#include <ESP8266WiFi.h>        // Include the Wi-Fi library

#include <NTPClient.h>

#include <WiFiUdp.h>


const char* ssid = "P307";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "bayanhdeptrai";     // The password of the Wi-Fi network

int ledWifiStatus = D1;
int pumpPush = D5; 
int timeSleep = 15;

unsigned long currentMillisWifi = 0;
unsigned long currentMillis = millis();

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

bool onPumps = false;
bool isDeepSleeped = false;

void handlerPumps() {
  digitalWrite(pumpPush, LOW);
  Serial.println("Cho bom 10s");
  delay(10000);
  digitalWrite(pumpPush, HIGH);
  
}


bool isWatered = false;
String timeSet = "01:30";

void handleTime() {
  String formattedTime = timeClient.getFormattedTime(); 
  String num = formattedTime.substring(0,5);
  Serial.println(num);
  if(num == timeSet && !isWatered) {
    handlerPumps();
    isWatered = true;
  }
}

bool isConnected = false;
unsigned long previosTime = 0;
void setup() {
  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  pinMode(pumpPush, OUTPUT);
  digitalWrite(pumpPush, HIGH);
  pinMode(ledWifiStatus, OUTPUT);
  pinMode(ledWifiStatus, HIGH);
  timeClient.begin();
  timeClient.setTimeOffset(25200);
  digitalWrite(D0, LOW);
}
void loop() {
  timeClient.update();
  if(WiFi.status() == WL_CONNECTED && !isConnected) {
    Serial.println("Connected");
    digitalWrite(ledWifiStatus, LOW);
    isConnected = true;
  }
  if(WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledWifiStatus, !digitalRead(ledWifiStatus));
    delay(500);
    isConnected = false;
  }  
    handleTime();
    if(isWatered == true) {
      Serial.println("Bat dau ngu dong 15s");
      ESP.deepSleep(timeSleep*1e6);
      digitalWrite(D0, HIGH);
    }
    // khi chay that thi setTimeSleep = 86390;
}