#include "Player.h"
#include "Game.h"
#include "Screen.h"
#include "Constants.h"
#include "Utiles.h"
#include "LightRing.h"

LightRing *ring = new LightRing();

Player **players = new Player *[4] {
  new Player(PLAYER_1_RED_LED_PIN, PLAYER_1_GREEN_LED_PIN, PLAYER_1_BUTTON_PIN),
    new Player(PLAYER_2_RED_LED_PIN, PLAYER_2_GREEN_LED_PIN, PLAYER_2_BUTTON_PIN),
    new Player(PLAYER_3_RED_LED_PIN, PLAYER_3_GREEN_LED_PIN, PLAYER_3_BUTTON_PIN),
    new Player(PLAYER_4_RED_LED_PIN, PLAYER_4_GREEN_LED_PIN, PLAYER_4_BUTTON_PIN),
};

Screen *screen = new Screen(RS, E, D4, D5, D6, D7);

const String *QUESTIONS = new String[NUM_OF_QUESTIONS]{ "What is your name?", "How old are you?", "Where are you from?" };

Game *game = new Game(players, screen, QUESTIONS, ring);


void setup() {
  Serial.begin(9600);
  ring->setGreenPercentage(15);

  registerPlayerPins(players);
  pinMode(STARTER_BUTTON_PIN, INPUT);

  screen->printScreen("Hello World");
}

void loop() {
  updatePlayersEnrolment(players);
  int starterButtonState = digitalRead(STARTER_BUTTON_PIN);


  if (isPressed(STARTER_BUTTON_PIN) && !game->hasStarted && Game::numOfPlayers >= 2) {
    game->hasStarted = true;
    game->startGame();
  } else if (isPressed(STARTER_BUTTON_PIN) && game->hasStarted) {
    game->nextRound();
  }

  if (game->hasStarted) {
    game->updateGame();
  }
}
