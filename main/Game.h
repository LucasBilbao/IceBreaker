#include "Player.h"
#include "Screen.h"
#include "LightRing.h"

#pragma once
#ifndef Game_h
#define Game_h
class Game {
  long startTime;
  long endTime;
  unsigned int currentPlayerIndex = -1;
  unsigned int nextPlayerIndex = -1;
  unsigned int questionIndex = 0;
  unsigned int playersPlayed = 0;
  Player **players;
  Screen *screen;
  String *questions;
  LightRing *ring;
public:
  static unsigned int numOfPlayers;
  bool hasStarted = false;

  Game(Player **, Screen *, String *, LightRing *);
  void startGame();
  void startCurrentTurn();
  void endCurrentTurn();
  void updateGame();
  void nextTurn();
  void nextRound();
  bool hasEveryonePlayed();
  void resetPlayers();
};
#endif