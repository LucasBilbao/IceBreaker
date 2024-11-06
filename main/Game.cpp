#include "Game.h"
#include "Constants.h"
#include <Arduino.h>

unsigned int Game::numOfPlayers = 0;

Game::Game(Player** players, Screen* screen, String* questions, LightRing *ring)
  : players(players), screen(screen), questions(questions), ring(ring) {}

void Game::startGame() {
  for (int i = 0; i < 4; ++i) {
    if (currentPlayerIndex == -1 && players[i]->isPlaying) {
      currentPlayerIndex = i;
      break;
    }
  }

  for (int i = currentPlayerIndex + 1; i < 4; ++i) {
    if (nextPlayerIndex == -1 && players[i]->isPlaying) {
      nextPlayerIndex = i;
      break;
    }
  }

  screen->printScreen(questions[questionIndex]);

  startCurrentTurn();
}

void Game::startCurrentTurn() {
  startTime = millis();
  endTime = startTime;
  digitalWrite(players[currentPlayerIndex]->RED_LED_PIN, LOW);
  digitalWrite(players[currentPlayerIndex]->GREEN_LED_PIN, HIGH);
}

void Game::endCurrentTurn() {
  players[currentPlayerIndex]->hasPlayedInRound = true;
  digitalWrite(players[currentPlayerIndex]->RED_LED_PIN, HIGH);
  digitalWrite(players[currentPlayerIndex]->GREEN_LED_PIN, LOW);
}

void Game::updateGame() {
  if (endTime - startTime <= DURATION_OF_TURN_MS - 10000) {
    endTime = millis();
  } else if (endTime - startTime <= DURATION_OF_TURN_MS) {
    players[currentPlayerIndex]->blink();
    endTime = millis();
  } else {
    nextTurn();
  }
}

void Game::nextTurn() {
  endCurrentTurn();
  currentPlayerIndex = nextPlayerIndex;
  startCurrentTurn();
  playersPlayed++;

  if (playersPlayed >= Game::numOfPlayers) {
    nextRound();
  }

  unsigned int i = currentPlayerIndex + 1;
  if (i == 4) {
    i = 0;
  }

  while (currentPlayerIndex == nextPlayerIndex && i != currentPlayerIndex) {
    if (i == 4) {
      i = 0;
    }

    if (players[i]->isPlaying) {
      nextPlayerIndex = i;
    }
    i++;
  }
}

void Game::nextRound() {
  if (!hasEveryonePlayed()) {
    return;
  }
  resetPlayers();
  questionIndex++;
  if (questionIndex == NUM_OF_QUESTIONS) {
    questionIndex = 0;
  }
  screen->printScreen(questions[questionIndex]);

  playersPlayed = 0;
}

bool Game::hasEveryonePlayed() {
  for (int i = 0; i < 4; ++i) {
    if (players[i]->isPlaying && !players[i]->hasPlayedInRound) {
      return false;
    }
  }
  return true;
}

void Game::resetPlayers(){
  for (int i = 0; i < 4; ++i) {
    if(players[i]->isPlaying){
      players[i]->hasPlayedInRound = false;
    }
  }
}
