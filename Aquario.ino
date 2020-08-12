#include <FastLED.h>
#define NUM_LEDS 144
#define DATA_PIN 8

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
}


void loop() {

  int a0 = analogRead(A0);
  int a1 = analogRead(A1);
  int a2 = analogRead(A2);
  int a0_1 = a0 * (255 / 1023.0);
  int a1_1 = a1 * (255 / 1023.0);
  int a2_1 = a2 * (255 / 1023.0);

  a0_1 = int(a0_1);
  a1_1 = int(a1_1);
  a2_1 = int(a2_1);

  /*  Serial.println(a0_1);
    Serial.println(a1_1);
    Serial.println(a2_1);
  */

  FastLED.showColor(CRGB(a0_1, a1_1, a2_1));
  delay(50);
}
