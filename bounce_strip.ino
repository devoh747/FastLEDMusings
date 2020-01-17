/*
 * move a dot with a tail across the strip
 * then program it to bounce at the ends
 * then move dots from the ends to the center and bounce the dot between them
 */

#include <FastLED.h>

#define NUM_LEDS 144
#define DATA_PIN 5
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define MAX_BRIGHTNESS 96  // higher than 128 and the strip draws too much power when using 60 LEDs
#define DELAY_INTERVAL 20

//Global Variables
byte hue = 0;

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000);    // give the board a moment to wake up
  Serial.begin(9600);


  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.clear();
}

void bounce(byte lowEnd, byte highEnd)  {

  // sanity check the low and high ends, so madness doesn't happen....
  delay(DELAY_INTERVAL);
  leds[lowEnd]=CHSV(hue,255,MAX_BRIGHTNESS);
  FastLED.show();

  delay(DELAY_INTERVAL);
  leds[lowEnd+1]=CHSV(hue,255,MAX_BRIGHTNESS);
  leds[lowEnd]=CHSV(hue,255,MAX_BRIGHTNESS/2);
  FastLED.show();

  delay(DELAY_INTERVAL);
  leds[lowEnd+2]=CHSV(hue,255,MAX_BRIGHTNESS);
  leds[lowEnd+1]=CHSV(hue,255,MAX_BRIGHTNESS/2);
  leds[lowEnd]=CHSV(hue,255,MAX_BRIGHTNESS/4);
  FastLED.show();

  for (int i = lowEnd+3; i < highEnd; i++) {
    delay(DELAY_INTERVAL);
    leds[i]=CHSV(hue,255,MAX_BRIGHTNESS);
    leds[i-1]=CHSV(hue,255,MAX_BRIGHTNESS/2);
    leds[i-2]=CHSV(hue,255,MAX_BRIGHTNESS/4);
    leds[i-3]=CHSV(0,0,0);
    FastLED.show();
  }
  
  delay(DELAY_INTERVAL);
  leds[highEnd-1]=CHSV(hue,255,MAX_BRIGHTNESS);
  leds[highEnd-2]=CHSV(hue,255,MAX_BRIGHTNESS/2);
  leds[highEnd-3]=CHSV(0,0,0);
  FastLED.show();

  delay(DELAY_INTERVAL);
  leds[highEnd-1]=CHSV(hue,255,MAX_BRIGHTNESS);
  leds[highEnd-2]=CHSV(0,0,0);
  FastLED.show();

//and back again

  delay(DELAY_INTERVAL);
  leds[highEnd-2]=CHSV(hue,255,MAX_BRIGHTNESS);
  leds[highEnd-1]=CHSV(hue,255,MAX_BRIGHTNESS/2);
  FastLED.show();

  delay(DELAY_INTERVAL);
  leds[highEnd-3]=CHSV(hue,255,MAX_BRIGHTNESS);
  leds[highEnd-2]=CHSV(hue,255,MAX_BRIGHTNESS/2);
  leds[highEnd-1]=CHSV(hue,255,MAX_BRIGHTNESS/4);
  FastLED.show();


  for (int i = highEnd - 4; i >= lowEnd; i--) {
    delay(DELAY_INTERVAL);
    leds[i]=CHSV(hue,255,MAX_BRIGHTNESS);
    leds[i+1]=CHSV(hue,255,MAX_BRIGHTNESS/2);
    leds[i+2]=CHSV(hue,255,MAX_BRIGHTNESS/4);
    leds[i+3]=CHSV(0,0,0);
    FastLED.show();
  }
  
  delay(DELAY_INTERVAL);
  leds[lowEnd]=CHSV(hue,255,MAX_BRIGHTNESS);
  leds[lowEnd+1]=CHSV(hue,255,MAX_BRIGHTNESS/2);
  leds[lowEnd+2]=CHSV(0,0,0);
  FastLED.show();

  delay(DELAY_INTERVAL);
  leds[lowEnd]=CHSV(hue,255,MAX_BRIGHTNESS);
  leds[lowEnd+1]=CHSV(0,0,0);
  FastLED.show();  
  
  delay(DELAY_INTERVAL);
  leds[lowEnd]=CHSV(0,0,0);
  FastLED.show();  
}

void loop() {
//  random16_add_entropy(random8());
//  hue=random8();  this isn't really random, need to learn more about random

  hue = 0;
  for(byte i = 1; i < 70; i++) {
    hue+=3;
    leds[i-1] = CHSV(hue,255,MAX_BRIGHTNESS);
    leds[NUM_LEDS-i] = CHSV(hue,255,MAX_BRIGHTNESS);
    bounce(i,NUM_LEDS-i);
    Serial.print("Hue = ");
    Serial.println(hue);
    
  }
  for(byte i = 70; i > 1; i--) {
    leds[i] = CHSV(0,0,0);
    leds[NUM_LEDS-i-1] = CHSV(0,0,0);
    bounce(i,NUM_LEDS-i);
    hue-=3;
    Serial.print("Hue = ");
    Serial.println(hue);
  }

}
