/*
Name: Destiny Bonillas
CWID: 887190072
Email: destinybonillas@csu.fullerton.edu

Name: Joseph Eggers
CWID: 885939488
Email: joseph.eggers@csu.fullerton.edu
*/

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
  int width_player = width_;
  int height_player = height_;
  int x_player = x_;
  int y_player = y_;
  if (width_player > width_game_element) {
    if (((width_game_element + x_game_element) - (width_player + x_player) >
             -width_player &&
         (width_game_element + x_game_element) - (width_player + x_player) <
             width_player) &&
        ((height_game_element + y_game_element) - (height_player + y_player) >
             -height_player &&
         (height_game_element + y_game_element) - (height_player + y_player) <
             height_player)) {
      return true;
    }
    return false;
  } else {
    // first if statment has to be player width (still have to change
    // and explain) Everyting else should be fine
    if (((width_game_element + x_game_element) - (width_player + x_player) >
             -width_player &&
         (width_game_element + x_game_element) - (width_player + x_player) <
             width_game_element) &&
        ((height_game_element + y_game_element) - (height_player + y_player) >
             -height_game_element &&
         (height_game_element + y_game_element) - (height_player + y_player) <
             height_game_element)) {
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
