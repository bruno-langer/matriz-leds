#include "BluetoothSerial.h"
#include <ArduinoJson.h>
#include <FastLED.h>

#define DATA_PIN 26
#define NUM_LEDS 144

CRGB leds[NUM_LEDS];

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

String msg;
char b1;
int tipo;
int cor;

BluetoothSerial ESPBT;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ESPBT.begin("ESP_LANGER"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Ativo");
  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {


  while ( ESPBT.available()) {
    msg  = ESPBT.readString();
    Serial.println(msg);
  }

  if (msg.length() > 1) {
    StaticJsonBuffer<100> doc;
    JsonObject& parsed = doc.parseObject(msg);

    // Test if parsing succeeds.
    if (!parsed.success()) { //Check for errors in parsing
      Serial.println("Parsing failed");
      delay(5000);
      return;
    }

    cor = parsed["cor"];
    tipo = parsed["tipo"];
  }

  if (tipo == 0) {
    FastLED.showColor(CRGB::Black);
    delay(100);
  }
  else if (tipo == 1) {

    FastLED.showColor(CHSV(cor, 255, 100));
    delay(100);
  }
  else if (tipo == 2) {
    for (int i = 0; i < 255; i++) {
      FastLED.showColor(CHSV(i, 255,100 ));
      delay(50);
      if(ESPBT.available()){
        break;
      }
    }
  }
  else if (tipo == 3) {
    for (int i = 0; i < NUM_LEDS; i++) {
      int aleatorio = random(-10, 10);
      int aleatorio2 = random(100);
      leds[i].setHSV(unsigned(cor + aleatorio), 255, 100);
      leds[i].nscale8(aleatorio2);
    }
    FastLED.show();
    delay(10);
  }

  msg = "\0";
}
