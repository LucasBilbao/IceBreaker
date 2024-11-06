#include <Arduino.h>

#pragma once
#ifndef Player_h
#define Player_h
class Player {
public:
  const unsigned int RED_LED_PIN;
  const unsigned int GREEN_LED_PIN;
  const unsigned int BUTTON_PIN;
  bool isPlaying = false;
  bool hasPlayedInRound = false;

  Player(unsigned int, unsigned int, unsigned int);
  
  void enrol();
  void unenrol();
  void blink();
};
#endif