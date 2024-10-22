#include <LiquidCrystal.h>

#pragma once
#ifndef Screen_h
#define Screen_h
class Screen: public LiquidCrystal {
public:
  Screen(int, int, int, int, int, int);
  void printScreen(String);
};

#endif