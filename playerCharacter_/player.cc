// Name: Destiny Bonillas
// CWID: 887190072
// Email: destinybonillas@csu.fullerton.edu

// Name: Joseph Eggers
// CWID: 885939488
// Email: joseph.eggers@csu.fullerton.edu

#include "player.h"

#include <iostream>
#include <string>
#include <vector>

#include "../cpputils/graphics/image.h"

using graphics::Image, graphics::Color, std::cin, std::cout, std::endl,
    std::string, std::vector;

// ---------- *** Player Class Start *** ---------------------
// ---------------- ** Start of Public Methods * ---------------------

// ---------------- * Constructors * -------------------------

// Default Constructor
    //the player size is 85 because that is what worked, my theory is that the pixel size difference is different on here vs firealpaca
Player::Player() : GameElement(60, 0, 70, 70), playerImage_ {"playerCharacter_/gnome1","playerCharacter_/gnome2","playerCharacter_/gnome3","playerCharacter_/gnome4"} {
  this->coordsUpdated_ = false;
  this->file_ = "gnome1";
  this->playerImageCycle_ = 0;
  this->file_ = playerImage_[playerImageCycle_];
  
  // Draw Character
  
}

// Constructor
Player::Player(int startingX, int startingY)
    : GameElement(startingX, startingY, 70, 70), playerImage_ {"playerCharacter_/gnome1","playerCharacter_/gnome2","playerCharacter_/gnome3","playerCharacter_/gnome4"} {
  this->coordsUpdated_ = true;
  this->playerImageCycle_ = 0;
  this->file_ = playerImage_[playerImageCycle_];
  // Draw Character
}
// Draw Character onto image
void Player::Draw(Image& image) {
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
      //if(playerColor.Red() == 0 && playerColor.Green() == 0 && playerColor.Blue() == 0 ) continue;
      if ((xOffSet < imgWidth && xOffSet >= 0) &&
          (yOffSet < imgHeight && yOffSet >= 0)) {
        image.SetColor(xOffSet, yOffSet, playerColor);
      } else {
        continue;
      }
    }
  }
  this->coordsUpdated_ = false;
  // Code for icrementing the image
  this->playerPhase_ = playerPhase_ + 1;
  if(playerPhase_ % 1 == 0){
    int temp = playerImageCycle_;
    temp = (temp + 1) % 4;
    this->playerImageCycle_ = temp;
    this->file_ = playerImage_[playerImageCycle_];
  } 
  if(playerPhase_ % 8 == 0) this->playerPhase_ = 0;
}

// Defining Move Function
void Player::Move(const Image& image) {
  // implememt later
}
//
// ---------- *** PlayerProjectile Class Start *** ----------------
// ---------------- ** Start of Public Methods * ---------------------

// ---------------- * Constructors * -------------------------

// Default Constructor
PlayerProjectile::PlayerProjectile() : GameElement(0, 0, 6, 10) {
  this->coordsUpdated_ = false;
  this->file_ = "playerProjectile";
  // Draw Character
  makeProjectile();
}

// Constructor
PlayerProjectile::PlayerProjectile(int startingX, int startingY)
    : GameElement(startingX, startingY, 6, 10) {
  this->coordsUpdated_ = true;
  this->file_ = "playerProjectile";
  // Draw Character
  makeProjectile();
}

// ---------------- * Public Methods  * -------------------------
// Draw Character onto image
void PlayerProjectile::Draw(Image& image) {
  // Initilize Images
  Image player;
  // Load Robot and Hide it so it Doesnt display
  player.Load(file_);
  //player.Hide();
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

// Defining Move Function
void PlayerProjectile::Move(const Image& image) {
  if (IsOutOfBounds(image) == true) {
    is_active_ = false;
    return;
  }
  this->y_ = y_ + velocity_;
}
// ---------------- ** Start of Private Methods * --------------------
void PlayerProjectile::makeProjectile() {
  Color center(153, 217, 234);
  Color second(78, 171, 252);
  Image image(width_, height_);
  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < height_; y++) {
      int random = rand() % 3 + 1;
      if (random % 3 == 0) {
        image.SetColor(x, y, second);
      } else {
        image.SetColor(x, y, center);
      }
    }
  }
  image.SaveImageBmp(file_);
}
