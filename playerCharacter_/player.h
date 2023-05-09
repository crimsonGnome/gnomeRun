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
#include "../opponentCharacter_/opponent.h"

using graphics::Image, graphics::Color, std::string, std::vector;
// Player
class Player : public GameElement {
 private:
  unsigned int playerPhase_;
  vector<string> playerImage_;
  unsigned int playerImageCycle_;

  // frequency affects the frame rate of gnome. currnely set to 1 in constructor
  // 1 frame shift per gnome
  unsigned int frequenceyOfImageCycle_;
 
  // Mehtod we have to add
  void UpdateImageCycle();

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
  double velocity_ = 20;
  // Private Member
 

 public:
  // Constructors
  PlayerProjectile();
  PlayerProjectile(int startingX, int startingY);

  // Draw function, needs to take reference to an image so the image is
  // being changed directly to the original image

  void Draw(Image& image) override;
  // Internal functions used by draw

  // Move player projectiles
  void Move(const Image& image) override;
};

#endif  // PLAYER_H
