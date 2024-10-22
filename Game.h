#include "Player.h"
#include "Screen.h"

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
public:
  static unsigned int numOfPlayers;
  bool hasStarted = false;

  Game(Player **, Screen *, String *);
  void startGame();
  void startCurrentTurn();
  void endCurrentTurn();
  void updateGame();
  void nextTurn();
  void nextRound();
};
#endif