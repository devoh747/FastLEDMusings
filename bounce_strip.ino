/*
 * move a dot with a tail across the strip
 * then program it to bounce at the ends
 * then move dots from the ends to the center and bounce the dot between them
 */

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
FASTLED_USING_NAMESPACE

#define NUM_LEDS 144
#define DATA_PIN 5
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define MAX_POWER_MILLIAMPS 500
#define MAX_BRIGHTNESS 96  
#define DELAY_INTERVAL 20

//Global Variables
byte gHue = 0;

CRGB gLEDs[NUM_LEDS];

void setup() {
  delay(3000);    // give the board a moment to wake up

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(gLEDs, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, MAX_POWER_MILLIAMPS);
}

void bounce(byte lowEnd, byte highEnd)  {

  // TODO: sanity check the low and high ends, so madness doesn't happen....
  
  delay(DELAY_INTERVAL);
  gLEDs[lowEnd]=CHSV(gHue,255,MAX_BRIGHTNESS);
  FastLED.show();

  delay(DELAY_INTERVAL);
  gLEDs[lowEnd+1]=CHSV(gHue,255,MAX_BRIGHTNESS);
  gLEDs[lowEnd]=CHSV(gHue,255,MAX_BRIGHTNESS/2);
  FastLED.show();

  delay(DELAY_INTERVAL);
  gLEDs[lowEnd+2]=CHSV(gHue,255,MAX_BRIGHTNESS);
  gLEDs[lowEnd+1]=CHSV(gHue,255,MAX_BRIGHTNESS/2);
  gLEDs[lowEnd]=CHSV(gHue,255,MAX_BRIGHTNESS/4);
  FastLED.show();

  for (int i = lowEnd+3; i < highEnd; i++) {
    delay(DELAY_INTERVAL);
    gLEDs[i]=CHSV(gHue,255,MAX_BRIGHTNESS);
    gLEDs[i-1]=CHSV(gHue,255,MAX_BRIGHTNESS/2);
    gLEDs[i-2]=CHSV(gHue,255,MAX_BRIGHTNESS/4);
    gLEDs[i-3]=CHSV(0,0,0);
    FastLED.show();
  }
  
  delay(DELAY_INTERVAL);
  gLEDs[highEnd-1]=CHSV(gHue,255,MAX_BRIGHTNESS);
  gLEDs[highEnd-2]=CHSV(gHue,255,MAX_BRIGHTNESS/2);
  gLEDs[highEnd-3]=CHSV(0,0,0);
  FastLED.show();

  delay(DELAY_INTERVAL);
  gLEDs[highEnd-1]=CHSV(gHue,255,MAX_BRIGHTNESS);
  gLEDs[highEnd-2]=CHSV(0,0,0);
  FastLED.show();

//and back again

  delay(DELAY_INTERVAL);
  gLEDs[highEnd-2]=CHSV(gHue,255,MAX_BRIGHTNESS);
  gLEDs[highEnd-1]=CHSV(gHue,255,MAX_BRIGHTNESS/2);
  FastLED.show();

  delay(DELAY_INTERVAL);
  gLEDs[highEnd-3]=CHSV(gHue,255,MAX_BRIGHTNESS);
  gLEDs[highEnd-2]=CHSV(gHue,255,MAX_BRIGHTNESS/2);
  gLEDs[highEnd-1]=CHSV(gHue,255,MAX_BRIGHTNESS/4);
  FastLED.show();


  for (int i = highEnd - 4; i >= lowEnd; i--) {
    delay(DELAY_INTERVAL);
    gLEDs[i]=CHSV(gHue,255,MAX_BRIGHTNESS);
    gLEDs[i+1]=CHSV(gHue,255,MAX_BRIGHTNESS/2);
    gLEDs[i+2]=CHSV(gHue,255,MAX_BRIGHTNESS/4);
    gLEDs[i+3]=CHSV(0,0,0);
    FastLED.show();
  }
  
  delay(DELAY_INTERVAL);
  gLEDs[lowEnd]=CHSV(gHue,255,MAX_BRIGHTNESS);
  gLEDs[lowEnd+1]=CHSV(gHue,255,MAX_BRIGHTNESS/2);
  gLEDs[lowEnd+2]=CHSV(0,0,0);
  FastLED.show();

  delay(DELAY_INTERVAL);
  gLEDs[lowEnd]=CHSV(gHue,255,MAX_BRIGHTNESS);
  gLEDs[lowEnd+1]=CHSV(0,0,0);
  FastLED.show();  
  
  delay(DELAY_INTERVAL);
  gLEDs[lowEnd]=CHSV(0,0,0);
  FastLED.show();  
}

void loop() {
  gHue = 0;
  for(byte i = 1; i < 70; i++) {
    gHue+=3;
    gLEDs[i-1] = CHSV(gHue,255,MAX_BRIGHTNESS);
    gLEDs[NUM_LEDS-i] = CHSV(gHue,255,MAX_BRIGHTNESS);
    bounce(i,NUM_LEDS-i);
  }
  
  for(byte i = 70; i > 1; i--) {
    gLEDs[i] = CHSV(0,0,0);
    gLEDs[NUM_LEDS-i-1] = CHSV(0,0,0);
    bounce(i,NUM_LEDS-i);
    gHue-=3;
  }

}
