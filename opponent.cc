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
   File name: opponent.cc
   Language: C++
   Build: sh build.sh
   Run: ./main
   Type: Class
   Purpose: Draws the opponent on screen and deals with opponent movement capability, keeps track of changing opponent state if
   collision detected with opponent projectile
======================================================================================================== */
#include "opponent.h"

#include <memory>
#include <random>

#include "cpputils/graphics/image.h"
#include "game_element.h"

using graphics::Image, graphics::Color, std::unique_ptr;

// -------------------- * Constructors * ---------------------

Opponent::Opponent() : GameElement(0, 0, 50, 50) {
  this->coordsUpdated_ = false;
  this->file_ = "opponentCharacter";
  this->launch_ = rand() % 25;
  // Draw character
  makeOpponent();
}

Opponent::Opponent(int startingX, int startingY)
    : GameElement(startingX, startingY, 50, 50) {
  this->coordsUpdated_ = true;
  this->file_ = "opponentCharacter";
  int temp = rand() % 25;
  this->launch_ = temp;
  // Draw character
  makeOpponent();
}

// Begin Draw Function
void Opponent::makeOpponent() {
  // creating size of Opponent
  Image opponent(50, 50);

  // code from milestone one to Draw Opponent
  // ***need to ADD implemnetation based on where opponent is on the screen***
  opponent.DrawCircle(25, 24, 14, 10, 87, 189);
  


  for (int x = 0; x < 50; x++) {
    // There is no pixels to edit outside of this Range
    for (int y = 0; y < 50; y++) {
      int red = opponent.GetRed(x, y);
      // If image red is == 255 then the picture is background then skip
      if (red == 255) {
        continue;
      } else {
        // random number
        int random = rand() % 2 + 1;
        // 1/4 chance of changing color
        if (random % 2 == 0) {
          // get Colors, then randomize off base
          int green = opponent.GetGreen(x, y);
          int blue = opponent.GetBlue(x, y);
          red = red + rand() % 14 + 1;
          blue = blue + rand() % 15 + 1;
          green = green + rand() % 15 + 1;
          Color tempColor(red, green, blue);
          opponent.SetColor(x, y, tempColor);
        } else {
          continue;
        }
      }
    }
  }
  opponent.SaveImageBmp(file_);
}

// code from milestone one to Draw Opponent
void Opponent::Draw(Image& image) {
  // Initilize Images
  Image player;
  // Load Robot and Hide it so it Doesnt display
  player.Load(file_);
  // ---------- Start of Variable Decleartion -----------
  // Constant Hieghts
  const int imgHeight = image.GetHeight();
  const int imgWidth = image.GetWidth();
  const int height = player.GetHeight();
  const int width = player.GetWidth();
  // ---------- End of Variable Decleartion -----------
  // ------------ Copy Image -----------------------
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      // Get color of the Image
      Color playerColor = player.GetColor(i, j);
      // off setting by the middle to draw image
      int xOffSet = x_ + i;
      int yOffSet = y_ + j;

      // Getting the image to draw on the location
      // only Draw Image if its range
      if ((xOffSet < imgWidth && xOffSet >= 0) &&
          (yOffSet < imgHeight && yOffSet >= 0)) {
        image.SetColor(xOffSet, yOffSet, playerColor);
      } else {
        continue;
      }
    }
  }
  this->coordsUpdated_ = false;
}

// Move Function Defined
void Opponent::Move(const Image& image) {
  if (IsOutOfBounds(image) == true) {
    is_active_ = false;
    return;
  }

  if (movingRight_) {
    this->x_ = x_ + velocity_;
  } else {
    this->x_ = x_ - velocity_;
  }
  this->y_--;
}

unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  if (counter_ % 25 == launch_) {
    unique_ptr<OpponentProjectile> opponent_projectile(
        new OpponentProjectile(x_ - 23, y_ -
         50));
    counter_++;
    return move(opponent_projectile);
  } else {
    counter_++;
    return nullptr;
  }
}
//
//
//
//
//
//
//
//
//

// Beginning functions for OpponentProjectile
// ---------------------- * Constructors * ----------------------
OpponentProjectile::OpponentProjectile() : GameElement(0, 0, 5, 5) {
  this->coordsUpdated_ = false;
  this->file_ = "opponentProjectile";
  this->truePosition_ = 0;
  // Draw Character
  makeOpponentProjectile();
}

// Constructor
OpponentProjectile::OpponentProjectile(int startingX, int startingY)
    : GameElement(startingX, startingY, 5, 5) {
  this->coordsUpdated_ = true;
  this->truePosition_ = startingY;
  this->file_ = "opponentProjectile";
  // Draw Character
  makeOpponentProjectile();
}

// Beginning Draw fucntion
void OpponentProjectile::makeOpponentProjectile() {
  // creating size of OpponentProjectile
  Image opponent_projectile(5, 5);

  // code from milestone one to Draw OpponentProjectile
  // ***need to ADD implemnetation based on where opponent_projectile is on
  // the screen***
  opponent_projectile.DrawCircle(2, 2, 4, 156, 3, 36);
  opponent_projectile.DrawCircle(1, 1, 3, 224, 49, 87);
  opponent_projectile.DrawCircle(3, 3, 1, 219, 4, 26);
  opponent_projectile.DrawCircle(4, 4, 2, 140, 22, 34);

  opponent_projectile.SaveImageBmp(file_);
}
void OpponentProjectile::Draw(Image& image) {
  // Initilize Images
  Image player;
  // Load Robot and Hide it so it Doesnt display
  player.Load(file_);
  player.Hide();
  // ---------- Start of Variable Decleartion -----------
  // Constant Hieghts
  const int imgHeight = image.GetHeight();
  const int imgWidth = image.GetWidth();
  const int height = player.GetHeight();
  const int width = player.GetWidth();
  // ---------- End of Variable Decleartion -----------
  // ------------ Copy Image -----------------------
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      // Get color of the Image
      Color playerColor = player.GetColor(i, j);
      // off setting by the middle to draw image
      int xOffSet = x_ + i;
      int yOffSet = y_ + j;

      // Getting the image to draw on the location
      // only Draw Image if its range
      if ((xOffSet < imgWidth && xOffSet >= 0) &&
          (yOffSet < imgHeight && yOffSet >= 0)) {
        image.SetColor(xOffSet, yOffSet, playerColor);
      } else {
        continue;
      }
    }
  }
  this->coordsUpdated_ = false;
}

// Move Function Defined
void OpponentProjectile::Move(const Image& image) {
  if (IsOutOfBounds(image) == true) {
    is_active_ = false;
    return;
  }
  this->truePosition_ = truePosition_ + velocity_ * time_ - 4.9 * time_ * time_;
  this->y_ = truePosition_;
  this->velocity_ = velocity_ - 9.8 * time_;
}
