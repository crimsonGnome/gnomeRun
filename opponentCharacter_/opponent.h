/*
Name: Destiny Bonillas
CWID: 887190072
Email: destinybonillas@csu.fullerton.edu

Name: Joseph Eggers
CWID: 885939488
Email: joseph.eggers@csu.fullerton.edu
*/

#ifndef OPPONENT_H
#define OPPONENT_H

#include <memory>

#include "../cpputils/graphics/image.h"
#include "../game_element.h"

using graphics::Image, std::string, std::unique_ptr, std::vector;

// not going to be used
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
  bool isEvil_ = false;
  int launch_;
  int counter_ = 0; // used for launching projectiles 
  unsigned int playerPhase_;
  vector<string> playerImage_;
  vector<string> evilImage_;
  unsigned int colorModifier_;
  unsigned int playerImageCycle_;

  // Private Memebers
  void UpdateImageCycle();


 public:
  // Constructors
  Opponent();
  Opponent(int startingX, int startingY);
  void Draw(Image& image) override;
  void SetMoveDirection(bool x) { this->movingRight_ = x; };
  bool GetIsEvil() { return isEvil_; };
  void SetIsEvil(bool isEvil) {this->isEvil_ = isEvil; };
  int GetLaunch() { return launch_; };

  // all other elements derived from Parent class
  // Move Function
  void Move(const Image& image) override;
  void MoveEvil(const Image& image, int x, int y, int score);

  unique_ptr<OpponentProjectile> LaunchProjectile();
};
#endif  // OPPONENT_H
