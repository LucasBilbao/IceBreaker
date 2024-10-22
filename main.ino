#include "Player.h"
#include "Game.h"
#include "Screen.h"
#include "Constants.h"
#include "Utiles.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN 22  // PIN to use for the digital input cable to the pixelring.
#define LED_COUNT 24

Adafruit_NeoPixel ring = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

Player **players = new Player *[4] {
  new Player(PLAYER_1_RED_LED_PIN, PLAYER_1_GREEN_LED_PIN, PLAYER_1_BUTTON_PIN),
    new Player(PLAYER_2_RED_LED_PIN, PLAYER_2_GREEN_LED_PIN, PLAYER_2_BUTTON_PIN),
    new Player(PLAYER_3_RED_LED_PIN, PLAYER_3_GREEN_LED_PIN, PLAYER_3_BUTTON_PIN),
    new Player(PLAYER_4_RED_LED_PIN, PLAYER_4_GREEN_LED_PIN, PLAYER_4_BUTTON_PIN),
};

Screen *screen = new Screen(RS, E, D4, D5, D6, D7);

const String *QUESTIONS = new String[NUM_OF_QUESTIONS]{ "What is your name?", "How old are you?", "Where are you from?" };

Game *game = new Game(players, screen, QUESTIONS);

long startTime;
long endTime;
unsigned long startLights;


void setup() {
  Serial.begin(9600);

  registerPlayerPins(players);

  startTime = millis();
  endTime = startTime;

  ring.begin();
  ring.show();
  ring.setBrightness(50);

  startLights = millis();
}

void loop() {
  updatePlayerSwitchStates(players);
  updatePlayersEnrolment(players);

  if (!game->hasStarted && Game::numOfPlayers >= 2) {
    if (endTime - startTime >= DURATION_UNTIL_GAME_STARTS_MS) {
      game->hasStarted = true;
      startTime = 0;
      endTime = 0;
      Serial.println("Game has started");
      game->startGame();
    } else {
      endTime = millis();
    }
  }

  if (game->hasStarted) {
    game->updateGame();
  }

  // // FIRST ROUND
  // if (millis() - startLights >= 0) {
  //   for (int i = 0; i < ring.numPixels(); i++) {
  //     ring.setPixelColor(i, 0, 0, 255);  // dark
  //     ring.show();
  //     delay(20);
  //   }
  // }
  // // delay(1000);

  // // SECOND ROUND
  // if (millis() - startLights >= 1000) {
  //   for (int i = 0; i < ring.numPixels(); i++) {
  //     ring.setPixelColor(i, 0, 255, 255);  // medium
  //     ring.show();
  //     delay(20);
  //   }
  // }
  // // delay(1000);

  // // THIRD ROUND
  // if (millis() - startLights >= 2000) {
  //   for (int i = 0; i < ring.numPixels(); i++) {
  //     ring.setPixelColor(i, 255, 255, 0);  // light
  //     ring.show();
  //     delay(20);
  //   }
  //   startLights = millis();
  // }
  // delay(1000);
}
