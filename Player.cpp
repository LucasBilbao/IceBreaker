#include "Player.h";

Player::Player(unsigned int redLedPin, unsigned int greenLedPin, unsigned int buttonPin)
  : RED_LED_PIN(redLedPin), GREEN_LED_PIN(greenLedPin), BUTTON_PIN(buttonPin) {
}

void Player::enrol() {
  isPlaying = true;
}

void Player::unenrol() {
  isPlaying = false;
}

void Player::updateSwitchState() {
  switchState = digitalRead(BUTTON_PIN);
}

void Player::blink() {
  digitalWrite(GREEN_LED_PIN, LOW);
  delay(500);
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(500);
}