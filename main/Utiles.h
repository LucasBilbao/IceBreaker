#include <Arduino.h>
#include "Player.h"
#include "Game.h"

#pragma once
#ifndef Utiles_h
#define Utiles_h

void updatePlayerEnrolment(Player *);

void updatePlayersEnrolment(Player **);

void registerPlayerPins(Player **);

bool isPressed(int);

#endif