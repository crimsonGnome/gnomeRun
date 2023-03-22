/*
Name: Destiny Bonillas
CWID: 887190072
Email: destinybonillas@csu.fullerton.edu

Name: Joseph Eggers
CWID: 885939488
Email: joseph.eggers@csu.fullerton.edu
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "../cpputils/graphics/image.h"
#include "../game_element.h"
#include "../opponent.h"

using graphics::Image, graphics::Color, std::string, std::vector;
// Player
class Player : public GameElement {
 private:
  unsigned int playerPhase_;
  vector<string> playerImage_;
  unsigned int playerImageCycle_;
 
  // Mehtod we have to add
  // We have to create this code.

 public:
  // Constructors
  Player();
  Player(int startingX, int startingY);

  // Draw function
  void Draw(Image& image) override;

  void Move(const Image& image) override;
};

// Player projectile
class PlayerProjectile : public GameElement {
 private:
  double velocity_ = 10;
  // Private Member
  void makeProjectile();

 public:
  // Constructors
  PlayerProjectile();
  PlayerProjectile(int startingX, int startingY);

  // Draw function, needs to take reference to an image so the image is
  // being changed directly to the original image

  void Draw(Image& image) override;
  // Internal functions used by draw

  // Move Function
  void Move(const Image& image) override;
};

#endif  // PLAYER_H
