/*  ESP8266 LDR ArduinoIDE Thingspeak IoT Example code
 *
 *  This sketch sends data via HTTP GET requests to api.thingspeak.com of the value on
 *  LDR sensor on ESP8266 development board - Wittyboard. You need an api_key from Thingspeak.
 * 
 *  Based on: https://vaasa.hacklab.fi/2016/02/06/esp8266-on-nodemcu-board-ds18b20-arduinoide-thingspeak/
 *  ESP8266 Witty: http://www.schatenseite.de/en/2016/04/22/esp8266-witty-cloud-module/
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "GetAPFunc.h"

const char* ssid;
const char* pass;
const char* SCAN;


// RGB or button pins are not used in LDR example
#define RED_PIN      7   // RGB Light pin at Arduino pin 3
#define GREEN_PIN    8   // RGB Light pin at Arduino pin 5
#define BLUE_PIN     9   // RGB Light pin at Arduino pin 6
#define BUTTON_PIN   4   // Alert When HIGH button
#define LDR_PIN      A0

char host[] = "api.thingspeak.com";
//char host[] = "https://api.thingspeak.com/update?api_key=4ITYPMBOC90G7DK4&field1=0";
String ApiKey = "4ITYPMBOC90G7DK4";
String path = "/update?key=" + ApiKey + "&field1=";

int ldr_value = 0;

void setup() {

  Serial.begin(115200);
  delay(1000);
  Serial.println(".");
  pinMode(LDR_PIN, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);

  

}

void loop() {
  
  SCAN = "";
  GetAP();
  
  
  Serial.print("Select an SSID\n");
  while(newData == false){
    recvWithEndMarker();
//    showNewData();
//    Serial.println(receivedChars);
    delay(20);
  }
//    strcpy(ssid, receivedChars);
    ssid = receivedChars;
    ssid = ssid;
    Serial.println(ssid);
    newData = false;

  Serial.print("Select Password\n");
    while(newData == false){
      recvWithEndMarker();
    delay(20);\
  }
    pass = receivedChars;
    Serial.println(pass);
    newData = false;
  

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  while(SCAN != "Scan"){
    recvWithEndMarker();
    SCAN = receivedChars;
    ldr_value = analogRead(LDR_PIN); // read input value and store it
    Serial.println(ldr_value);
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }
  
 
    client.print(String("GET ") + path + ldr_value + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n\r\n");
    
    analogWrite(2, static_cast<int>(PWMRANGE * 0.01 * 80));
    delay(800);            
    digitalWrite(2, 1);
    
    delay(6000);
}
}
