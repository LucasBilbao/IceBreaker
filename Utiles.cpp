#include "Utiles.h"

void updatePlayerSwitchStates(Player **players) {
  for (int i = 0; i < 4; ++i) {
    players[i]->updateSwitchState();
  }
}

void updatePlayerEnrolment(Player *player) {
  if (player->switchState == HIGH) {
    if (!player->isPlaying) {
      player->enrol();
      Game::numOfPlayers++;
    } else {
      player->unenrol();
      Game::numOfPlayers--;
    }

    if (player->isPlaying) {
      digitalWrite(player->RED_LED_PIN, HIGH);
      digitalWrite(player->GREEN_LED_PIN, LOW);
    } else {
      digitalWrite(player->GREEN_LED_PIN, LOW);
      digitalWrite(player->RED_LED_PIN, LOW);
    }
    delay(500);
  }
}

void updatePlayersEnrolment(Player **players) {
  for (int i = 0; i < 4; ++i) {
    updatePlayerEnrolment(players[i]);
  }
}

void registerPlayerPins(Player **players) {
  for (int i = 0; i < 4; ++i) {
    pinMode(players[i]->RED_LED_PIN, OUTPUT);
    pinMode(players[i]->GREEN_LED_PIN, OUTPUT);
    pinMode(players[i]->BUTTON_PIN, INPUT);
  }
}
