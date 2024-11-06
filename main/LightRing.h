#include <Adafruit_NeoPixel.h>

#pragma once
#ifndef LightRing_h
#define LightRing_h
class LightRing : public Adafruit_NeoPixel {
public:
  LightRing();
  void setGreenPercentage(int);
};

#endif