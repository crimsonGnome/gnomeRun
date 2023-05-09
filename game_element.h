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
   File name: game_element.h
   Language: C++
   Build: sh build.sh
   Run: ./main
   Type: Class
   Purpose: Keeps track of x, y, width, and height of a game element, checks activity of a character, checks if game element is out of bounds,
   and when something is intersecting with.
======================================================================================================== */
#include <string>

#include "cpputils/graphics/image.h"

using graphics::Image, graphics::Color, std::string;

#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

class GameElement {
 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  string file_;
  bool coordsUpdated_;
  bool is_active_ = true;

 public:
  // Constructors
  GameElement() { x_ = 24, y_ = 15, width_ = 67, height_ = 60; }
  GameElement(int startingX, int startingY, int kWidth, int kHeight);
  // Getters
  int GetX();
  int GetY();
  int GetWidth();
  int GetHeight();
  bool GetIsActive();
  // Setters
  void SetX(int x);
  void SetY(int y);
  void SetIsActive(bool is_active);

  // Draw function
  virtual void Draw(Image& image) = 0;

  // Move fucntion
  virtual void Move(const Image& image) = 0;

  // IntersectsWith Function
  bool IntersectsWith(GameElement* game_element);

  // IsOutOfBounds
  bool IsOutOfBounds(const Image& image);
};

#endif  // GAME_ELEMENT_H
