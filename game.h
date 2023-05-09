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
  Date of last update: 2023 May 03
  Date of reorganization of comments: 2023 May 08
  Files in this program: game_element, game, player, opponent, main
  Status: Finished.  The program was tested extensively with no errors in Ubuntu 20.04
This file
   File name: game.h
   Language: C++
   Build: sh build.sh
   Run: ./main
   Type: Class
   Purpose: Creates game characters, initalizes game screen, deals with animation and mouse events, keeps track of player score
======================================================================================================== */
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "opponentCharacter_/opponent.h"
#include "playerCharacter_/player.h"

using std::vector, std::unique_ptr;

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 private:
  graphics::Image gameScreen_;
  vector<unique_ptr<Opponent>> opponent_;
  vector<unique_ptr<OpponentProjectile>> opponentProjectile_;
  vector<unique_ptr<PlayerProjectile>> playerProjectile_;
  Player player_;
  int score_ = 0;
  bool status_ = true;
  unsigned int gameScreenX_ = 0;
  int backgroundY_ = 0;
  int backgroundX_ = 0;
  unsigned int firedCounter_ = 0;
  bool game_started_ = false;

  // Private Function
  void FirePlayerProjectile(Player&);
  void DrawBackgroundImage();
  void Restart();


 public:
  // constructors
  Game();
  Game(int height, int width);

  // Getters (referenced)
  graphics::Image& GetGameScreen() { return gameScreen_; };
  vector<unique_ptr<Opponent>>& GetOpponents() { return opponent_; };
  vector<unique_ptr<OpponentProjectile>>& GetOpponentProjectiles() {
    return opponentProjectile_;
  };
  vector<unique_ptr<PlayerProjectile>>& GetPlayerProjectiles() {
    return playerProjectile_;
  };
  Player& GetPlayer() { return player_; };
  int GetScore() { return score_; };
  bool HasLost() { return !status_; };

  // Memeber Functions
  void CreateOpponents();
  void Init();
  void UpdateScreen();
  void Start();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep();
  void OnMouseEvent(const graphics::MouseEvent& event);
  void RemoveInactive();
  void LaunchProjectiles();
};

#endif
