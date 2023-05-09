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
   File name: opponent.h
   Language: C++
   Build: sh build.sh
   Run: ./main
   Type: Class
   Purpose: Draws the opponent on screen and deals with opponent movement capability, keeps track of changing opponent state if
   collision detected with opponent projectile
======================================================================================================== */
#ifndef OPPONENT_H
#define OPPONENT_H

#include <memory>

#include "cpputils/graphics/image.h"
#include "game_element.h"

using graphics::Image, std::string, std::unique_ptr;

class OpponentProjectile : public GameElement {
 private:
  double velocity_ = 10;
  double time_ = .1;
  double truePosition_;

 public:
  // Constructors
  OpponentProjectile();
  OpponentProjectile(int startingX, int startingY);

  // Draw Funtions
  void Draw(Image& image) override;

  void makeOpponentProjectile();
  // all other elements derived from Parent class

  // Move Function
  void Move(const Image& image) override;
};

class Opponent : public GameElement {
 private:
  int velocity_ = 4;
  bool movingRight_ = true;
  int launch_;
  int counter_ = 0;

 public:
  // Constructors
  Opponent();
  Opponent(int startingX, int startingY);
  void Draw(Image& image) override;
  void makeOpponent();
  void SetMoveDirection(bool x) { this->movingRight_ = x; };

  int GetLaunch() { return launch_; };

  // all other elements derived from Parent class
  // Move Function
  void Move(const Image& image) override;

  unique_ptr<OpponentProjectile> LaunchProjectile();
};
#endif  // OPPONENT_H
