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
   File name: game_element.cc
   Language: C++
   Build: sh build.sh
   Run: ./main
   Type: Class
   Purpose: Keeps track of x, y, width, and height of a game element, checks activity of a character, checks if game element is out of bounds,
   and when something is intersecting with.
======================================================================================================== */
#include "game_element.h"

#include <string>

#include "cpputils/graphics/image.h"

using graphics::Image, graphics::Color, std::string;

GameElement::GameElement(int startingX, int startingY, int kWidth,
                         int kHeight) {
  this->x_ = startingX;
  this->y_ = startingY;
  this->width_ = kWidth;
  this->height_ = kHeight;
}

// Getters
int GameElement::GetX() { return this->x_; }
int GameElement::GetY() { return this->y_; }
int GameElement::GetWidth() { return this->width_; }
int GameElement::GetHeight() { return this->height_; }
bool GameElement::GetIsActive() { return this->is_active_; }

// Setters
void GameElement::SetX(int x) {
  this->x_ = x;
  this->coordsUpdated_ = true;
}
void GameElement::SetY(int y) {
  this->y_ = y;
  this->coordsUpdated_ = true;
}
void GameElement::SetIsActive(bool is_active) { this->is_active_ = is_active; }

// IntersectsWith Function Defined
bool GameElement::IntersectsWith(GameElement* game_element) {
  int width_game_element = game_element->GetWidth();
  int height_game_element = game_element->GetHeight();
  int x_game_element = game_element->GetX();
  int y_game_element = game_element->GetY();
  int width_player = width_ - 15;
  int height_player = height_ - 15;
  int x_player = x_ + 15;
  int y_player = y_ + 15;

  if (width_player > width_game_element) {
        //width and x position
    if (((width_game_element + x_game_element) - (width_player + x_player) > - width_player &&
         (width_game_element + x_game_element) - (width_player + x_player) < width_player) &&
         //height and y position
        ((height_game_element + y_game_element) - (height_player + y_player) > - height_player &&
         (height_game_element + y_game_element) - (height_player + y_player) < height_player)) {
          //characters overlap
          return true;
    }
    //Characters don't overlap
    return false;
  } else {
    // first if statment has to be player width (still have to change
    // and explain) Everyting else should be fine
        //width and x position
    if (((width_game_element + x_game_element) - (width_player + x_player) > - width_player &&
         (width_game_element + x_game_element) - (width_player + x_player) < width_game_element) &&
        //height and y position
        ((height_game_element + y_game_element) - (height_player + y_player) > - height_game_element &&
         (height_game_element + y_game_element) - (height_player + y_player) < height_game_element)) {
            //characters overlap
            return true;
            
    }
    return false;
  }
}


// IsOutOfBounds Function Defined
bool GameElement::IsOutOfBounds(const Image& image) {
  if (x_ < image.GetWidth() && y_ < image.GetHeight() && x_ > 0 && y_ > 0) {
    return false;
  }
  return true;
}



