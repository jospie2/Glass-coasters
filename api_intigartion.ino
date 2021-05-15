#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FastLED.h>
#define NUM_LEDS  11 // Number of LEDS
#define LED_PIN   12 // Pin of the LEDS
CRGB leds[NUM_LEDS];
uint8_t hue = 0;
const char* ssid     = ""; //Your WIFI ssid
const char* password = ""; // your WiFi password

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);

  Serial.begin(115200);
WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
   
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());



}






void loop() {
 

    if (WiFi.status() == WL_CONNECTED){

    WiFiClient client;

 HTTPClient http; //Object of class HTTPClient
    http.useHTTP10(true);
http.begin("");//the URL of your api
http.GET();

// Parse response
DynamicJsonDocument doc(2048);
deserializeJson(doc, http.getStream());
int brightness = doc["brighness"];
  FastLED.setBrightness(brightness);
if(doc["Status"]=="rainbow"){
  fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  FastLED.show();
  }
  if(doc["Status"]=="green"){
fill_solid(leds, NUM_LEDS, CRGB::Green);
FastLED.show();
  }
    if(doc["Status"]=="red"){
fill_solid(leds, NUM_LEDS, CRGB::Red);
FastLED.show();
  }
     if(doc["Status"]=="blue"){
fill_solid(leds, NUM_LEDS, CRGB::Blue);
FastLED.show();
  }
      if(doc["Status"]=="lightblue"){
fill_solid(leds, NUM_LEDS, CRGB::SkyBlue);
FastLED.show();
  }
   if(doc["Status"]=="white"){
fill_solid(leds, NUM_LEDS, CRGB::White);
FastLED.show();
  }
   if(doc["Status"]=="purple"){
fill_solid(leds, NUM_LEDS, CRGB::Purple);
FastLED.show();
  }
     if(doc["Status"]=="colourchange"){
for (int i = 0; i < NUM_LEDS; i++) {
    //leds[i] = CHSV(hue, 255, 255);
    leds[i] = CHSV(hue + (i * 10), 255, 255);
   
  }

 EVERY_N_MILLISECONDS(1){
 
    hue++;
  }

  FastLED.show();
  }
          if(doc["Status"]=="off"){
fill_solid(leds, NUM_LEDS, CRGB::Black);
FastLED.show();
  }
    }
    else{
      fill_solid(leds, NUM_LEDS, CRGB::Black);
FastLED.show();}}
