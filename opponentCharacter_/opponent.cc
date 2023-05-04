/*
Name: Destiny Bonillas
CWID: 887190072
Email: destinybonillas@csu.fullerton.edu

Name: Joseph Eggers
CWID: 885939488
Email: joseph.eggers@csu.fullerton.edu
*/
#include "opponent.h"

#include <memory>
#include <random>

#include "../cpputils/graphics/image.h"
#include "../game_element.h"

using graphics::Image, graphics::Color, std::unique_ptr, std::vector;

// -------------------- * Constructors * ---------------------

Opponent::Opponent() : GameElement(0, 0, 75, 75), playerImage_ {"opponentCharacter_/greenboi1.bmp","opponentCharacter_/greenboi2.bmp","opponentCharacter_/greenboi3.bmp","opponentCharacter_/greenboi4.bmp",
                                                                "opponentCharacter_/orangeboi1.bmp","opponentCharacter_/orangeboi2.bmp","opponentCharacter_/orangeboi3.bmp","opponentCharacter_/orangeboi4.bmp"                         
  } {
  this->coordsUpdated_ = false;
  this->file_ = "greenboi1.bmp";
  this->launch_ = rand() % 25;
  this->playerImageCycle_ = rand() % 4;
  this->playerPhase_ = playerImageCycle_ * rand() % 5;
  this->colorModifier_ = rand() % 2;
  this->file_ = playerImage_[playerImageCycle_ ];
  // Draw character

}

Opponent::Opponent(int startingX, int startingY)
    : GameElement(startingX, startingY, 75, 75), playerImage_ {"opponentCharacter_/greenboi1.bmp","opponentCharacter_/greenboi2.bmp","opponentCharacter_/greenboi3.bmp","opponentCharacter_/greenboi4.bmp",
                                                                "opponentCharacter_/orangeboi1.bmp","opponentCharacter_/orangeboi2.bmp","opponentCharacter_/orangeboi3.bmp","opponentCharacter_/orangeboi4.bmp"                         
                                              } , evilImage_ {"opponentCharacter_/evilfairy1.bmp","opponentCharacter_/evilfairy2.bmp","opponentCharacter_/evilfairy3.bmp","opponentCharacter_/evilfairy4.bmp","opponentCharacter_/evilfairy5.bmp"}
  {
  this->coordsUpdated_ = true;
  int temp = rand() % 25;
  this->launch_ = temp;
  this->playerImageCycle_ = rand() % 4;
  this->playerPhase_ = playerImageCycle_ * rand() % 10;
  this->colorModifier_ = rand() % 2;
  this->file_ = playerImage_[playerImageCycle_ +  (4 * colorModifier_)];
  // Draw character
  
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
      if(playerColor.Red() == 255 && playerColor.Green() == 255 && playerColor.Blue() == 255){
        continue;
      }
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
  this->playerPhase_ = playerPhase_ + 1;

  if(isEvil_){
    if(playerPhase_ % 1 == 0){
      int temp = playerImageCycle_;
      temp = (temp + 1) % 5;
      this->playerImageCycle_ = temp;
      this->file_ = evilImage_[playerImageCycle_];
    } 
    if(playerPhase_ % 5 == 0) this->playerPhase_ = 0;
  } else {
    if(playerPhase_ % 2 == 0){
      int temp = playerImageCycle_;
      temp = (temp + 1) % 4;
      this->playerImageCycle_ = temp;
      this->file_ = playerImage_[playerImageCycle_ +  (4 * colorModifier_)];
    } 
    if(playerPhase_ % 8 == 0) this->playerPhase_ = 0;
  }
  
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

// Move Function Defined
void Opponent::MoveEvil(const Image& image, int x, int y) {
  if (IsOutOfBounds(image) == true) {
    is_active_ = false;
    return;
  }
  int moveY = random() % 3 + 1;

  if (movingRight_) {
    this->x_ = x_ + velocity_;
  } else {
    this->x_ = x_ - velocity_;
  }

  // moveY
  if(moveY % 3 != 0){
    if(y_ > y ){
      this->y_ = y_ - velocity_;
    } else {
      this->y_ = y_ + velocity_;
    }
  } else {
    if(y_ > y ){
      this->y_ = y_ - ( 2 * velocity_);
    } else {
      this->y_ = y_ + ( 2 * velocity_);
    }
  }
  
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
