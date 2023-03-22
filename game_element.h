/*
Name: Destiny Bonillas
CWID: 887190072
Email: destinybonillas@csu.fullerton.edu

Name: Joseph Eggers
CWID: 885939488
Email: joseph.eggers@csu.fullerton.edu
*/

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
  GameElement() { x_ = 0, y_ = 0, width_ = 50, height_ = 50; }
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
