#include <FastLED.h>
#define NUM_LEDS  11 // the Number of leds
#define LED_PIN   12 // the pin for the leds
CRGB leds[NUM_LEDS];
uint8_t hue = 0;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);//setting up FastLED
}






void loop() {
 

  
  fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS); // makes an cool rainbow efekt
  FastLED.show();
  
   
for (int i = 0; i < NUM_LEDS; i++) {//makes an colour change efekt
    //leds[i] = CHSV(hue, 255, 255);
    leds[i] = CHSV(hue + (i * 10), 255, 255);
   
  }

 EVERY_N_MILLISECONDS(1){
 
    hue++;
  }

  FastLED.show();
 }
