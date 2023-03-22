/*
Name: Destiny Bonillas
CWID: 887190072
Email: destinybonillas@csu.fullerton.edu

Name: Joseph Eggers
CWID: 885939488
Email: joseph.eggers@csu.fullerton.edu
*/

#include <iostream>

#include "game.h"
#include "game_element.h"
#include "opponent.h"
#include "playerCharacter_/player.h"

int main() {
  // create Game object
  Game game;
  // Init initializes all game elements
  game.Init();
  // Start to display the game screen
  game.Start();
  return 0;
}
