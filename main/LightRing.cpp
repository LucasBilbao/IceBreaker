#include "LightRing.h"
#include "Constants.h"
#include <Adafruit_NeoPixel.h>

LightRing::LightRing()
  : Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800) {
  begin();
  show();
  setBrightness(50);
}

void LightRing::setGreenPercentage(int percentage) {
  int greenLights = numPixels() * percentage;
  Serial.print(numPixels());
  for (int i = 0; i < numPixels(); i++) {
    if (i + 1 <= greenLights) {
      setPixelColor(i, 0, 255, 0);
      continue;
    }

    setPixelColor(i, 255, 0, 0);
    show();
  }
}