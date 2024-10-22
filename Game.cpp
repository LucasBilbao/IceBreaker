#include "Game.h"
#include "Constants.h"
#include <Arduino.h>

unsigned int Game::numOfPlayers = 0;

Game::Game(Player** players, Screen* screen, String* questions)
  : players(players), screen(screen), questions(questions) {}

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
  digitalWrite(players[currentPlayerIndex]->RED_LED_PIN, HIGH);
  digitalWrite(players[currentPlayerIndex]->GREEN_LED_PIN, LOW);
}

void Game::updateGame() {
  if (endTime - startTime <= DURATION_BEFORE_BLINKING_MS) {
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

  if(playersPlayed == Game::numOfPlayers){
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

void Game::nextRound(){
  questionIndex++;
  if(questionIndex == NUM_OF_QUESTIONS){
    questionIndex = 0;
  }
  screen->printScreen(questions[questionIndex]);

  playersPlayed = 0;
}
