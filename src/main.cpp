#include <Arduino.h>

#include <ESP8266WiFi.h>        // Include the Wi-Fi library

#include <NTPClient.h>

#include <WiFiUdp.h>


const char* ssid     = "P307";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "bayanhdeptrai";     // The password of the Wi-Fi network

int led = D4;
int ledWifiStatus = D0;
int led1 = D2;
int led2 = D3;
int i=0;
unsigned long preMillisForLed1  = 0;
unsigned long preMillisForLed2  = 0;
unsigned long currentMillisWifi = 0;
unsigned long currentMillis = millis();
unsigned long led1Delay = 2000;
unsigned long led2Delay = 3000;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

char hour[5];


// void handlerPumps() {
//   digitalWrite(led, LOW);
//   delaymillis(1000);  
//   digitalWrite(led, HIGH);
//   delaymillis(1000);
// }

// void handleTime() {
//   String formattedTime = timeClient.getFormattedTime();
//   hour[0] = '2';
//   hour[1] = '0';
//   Serial.print("Formatted Time: ");
//   Serial.println(formattedTime);
//   if (hour[0] == formattedTime[0] && hour[1] == formattedTime[1]){
//     handlerPumps();   
//   }
//   delaymillis(2000);
// }

bool isConnected = false;

void setup() {
  Serial.begin(115200); 
  WiFi.begin(ssid, password);        // Start the Serial communication to send messages to the computer
  pinMode(ledWifiStatus, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
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
  
  currentMillis = millis();
  // led1 delay with 2000ms
  if(currentMillis - preMillisForLed1 >= 1000) {
    preMillisForLed1 = millis();
    if(digitalRead(led1) == LOW) {
      digitalWrite(led1, HIGH);
    } 
    else digitalWrite(led1, LOW);
  
  }
  // led2 delay with 3000ms
  if(millis() - preMillisForLed2 >= 2000) {
    preMillisForLed2 = millis();
    if(digitalRead(led2) == LOW) {
      digitalWrite(led2, HIGH);
    } 
    else digitalWrite(led2, LOW);
  
  }
}