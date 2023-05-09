/*=====================================================================================================================
Program name: "Gnome Run"
 Copyright (C) 2023.                                                                           
                                                                                                                          
This file is part of the software program "Gnome Run".
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License   
version 3 as published by the Free Software Foundation.                                                                    
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied          
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.     
A copy of the GNU General Public License v3 is available here:  <https:;www.gnu.org/licenses/>.                            
=========================================================================================================================

Author information
Author name: Joseph Eggers, Destiny Bonillas, Marriam Jawaid, Aubrianna Sample

Program information
  Program name: Gnome Run
  Programming languages: C++
  Date program began: 2023 February 07
  Date of last update: 2023 April 24
  Date of reorganization of comments: 2023 May 08
  Files in this program: game_element, game, player, opponent, main
  Status: Finished.  The program was tested extensively with no errors in Ubuntu 20.04
This file
   File name: main.cc
   Language: C++
   Build: sh build.sh
   Run: ./main
   Type: int
   Purpose: Calls start() and init() function located in game.cc to initialize and start game.
======================================================================================================== */
#include <iostream>

#include "game.h"
#include "game_element.h"
#include "opponentCharacter_/opponent.h"
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
