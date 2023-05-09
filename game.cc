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
   File name: game.cc
   Language: C++
   Build: sh build.sh
   Run: ./main
   Type: Class
   Purpose: Creates game characters, initalizes game screen, deals with animation and mouse events, keeps track of player score
======================================================================================================== */
#include "game.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

#include "cpputils/graphics/image.h"
#include "opponentCharacter_/opponent.h"
#include "playerCharacter_/player.h"

using graphics::Image, std::cout, std::string, std::vector, std::unique_ptr, std::thread;

// ---------------- Start of game Class ----------------------------
// ---------------- Start of Game Constructors ---------------------

std::mutex image_mutex;

Game::Game() {
  this->gameScreen_.Initialize(500, 800);
  Player crimsonGnome(375, 50);
  this->player_ = crimsonGnome;
}

Game::Game(int height, int width) {
  this->gameScreen_.Initialize(height, width);
  Player crimsonGnome(375, 50);
  this->player_ = crimsonGnome;
}

// ---------------- End of Game Constructors -----------------------
// ---------------- Start of Game Memeber Functions ----------------
// ---------------- Start of Game (Private) Memeber Functions ------

void Game::FirePlayerProjectile(Player& crimsonGnome) {
  // Vector for player projectiles
  vector<unique_ptr<PlayerProjectile>>& playerProjectileVect =
      GetPlayerProjectiles();
  // Create a unique pointer to player projectile
  unique_ptr<PlayerProjectile> beam(
      new PlayerProjectile(crimsonGnome.GetX(), crimsonGnome.GetY()));
  // Push player projectile to vector
  playerProjectileVect.push_back(move(beam));
}

// ---------------- Start of Game (Public) Memeber Functions ------
bool game_started_ = false;
graphics::Image start_screen_;

void Game::CreateOpponents() {
  // Init hoot hoots

  vector<unique_ptr<Opponent>>& opponentVector = opponent_;
  unique_ptr<Opponent> owl0(new Opponent(100, 550));
  unique_ptr<Opponent> owl1(new Opponent(200, 450));
  unique_ptr<Opponent> owl2(new Opponent(300, 550));
  unique_ptr<Opponent> owl3(new Opponent(350, 450));
  unique_ptr<Opponent> owl4(new Opponent(400, 550));

  // Add hoot hoots to array
  opponentVector.push_back(move(owl0));
  opponentVector.push_back(move(owl1));
  opponentVector.push_back(move(owl2));
  opponentVector.push_back(move(owl3));
  opponentVector.push_back(move(owl4));

  UpdateScreen();
}

void BackgroundLoop(int start, int stop, Image& image, Image& background, int backgroundY_){
  // thread 1 
    
    for(unsigned int i = start; i < stop; ++i){
        
      for(unsigned int k = 0; k < image.GetWidth(); ++k){
       
        // off setting by the middle to draw image
        int yOffSet = backgroundY_ + i;

        Color backgroundColor = background.GetColor(k, yOffSet % 2400);

        // std::unique_lock<std::mutex> lockChild(image_mutex);
        image.SetColor(k, i, backgroundColor);
        
      }
      
    }
}

void Game::Init() {
  start_screen_.Load("startscreen.bmp");
  // Setting New player position
  Image& image = GetGameScreen();
  image.AddMouseEventListener(*this);
  image.AddAnimationEventListener(*this);
}

void Game::MoveGameElements() {
  // Get Vectors
  Image& image = GetGameScreen();
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  vector<unique_ptr<OpponentProjectile>>& opponent_projectile =
      GetOpponentProjectiles();
  Player& player = GetPlayer();
  int playerx = player.GetX();
  vector<unique_ptr<PlayerProjectile>>& player_projectile =
      GetPlayerProjectiles();
  // Block owl movements move right or left
  // TODO: ---------------------------------------------------------
  // ---------------------------------------------------------
  if (opponent[opponent.size() - 1]->GetX() > 440) {
    for (int i = 0; i < opponent.size(); i++) {
      opponent[i]->SetMoveDirection(false);
    }
  } else if (opponent[0]->GetX() < 10) {
    for (int i = 0; i < opponent.size(); i++) {
      opponent[i]->SetMoveDirection(true);
    }
  }
  // Move all the images
  for (int i = 0; i < opponent.size(); i++) {
    if(opponent[i]->GetIsEvil()){
      opponent[i]->MoveEvil(image, player.GetX(), player.GetY());
    } else {
      opponent[i]->Move(image);
    }
    
  }
  // for (int i = 0; i < opponent_projectile.size(); i++) {
  //   opponent_projectile[i]->Move(image);
  // }
  for (int i = 0; i < player_projectile.size(); i++) {
    player_projectile[i]->Move(image);
  }
  // this is the fire counter looop
  // if projectile was fired increment counter
  if(firedCounter_ != 0){
    firedCounter_++;
    // if counter == 5 then change to 0
    if(firedCounter_ % 10 == 0){
      this->firedCounter_ = 0;
    }
  }
}

void Game::FilterIntersections() {
  Player& player = GetPlayer();
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  // for opponent and player
  for (int i = 0; i < opponent.size(); i++) {
    if (player.IntersectsWith(opponent[i].get())) {
      opponent[i]->SetIsActive(false);
      player.SetIsActive(false);
      this->status_ = false;
    }
  }
  vector<unique_ptr<OpponentProjectile>>& opponent_projectile =
      GetOpponentProjectiles();
  // for opponent projectiles and player
  for (int i = 0; i < opponent_projectile.size(); i++) {
    if (player.IntersectsWith(opponent_projectile[i].get())) {
      opponent_projectile[i]->SetIsActive(false);
      player.SetIsActive(false);
      this->status_ = false;
    }
  }

  vector<unique_ptr<PlayerProjectile>>& player_projectile =
      GetPlayerProjectiles();
  for (int j = 0; j < player_projectile.size(); j++) {
    for (int i = 0; i < opponent.size(); i++) {
      if (opponent[i]->IntersectsWith(player_projectile[j].get())) {
        player_projectile[j]->SetIsActive(false);
        opponent[i]->SetIsActive(false);
        if(opponent[i]->GetIsEvil() == false){
          for (int k = 0; k < opponent.size(); k++){
             opponent[k]->SetIsEvil(true);
          }
        }
        if (player.GetIsActive()) {
          this->score_++;
        }
      }
    }
  }
}

// Draw Background Image 
void Game::DrawBackgroundImage(){
  Image& image = GetGameScreen();
  Image background;
  int backgroundY = backgroundY_;
  background.Load("background.bmp");
  // thread 1 
  BackgroundLoop( 0, 800, image, background, backgroundY);

  this->backgroundY_ = backgroundY_ + 2;
  if(backgroundY_ >= 2400){
      backgroundY_ = 1;
  }

}

void Game::RemoveInactive() {
  // Get vector for opponent
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  // Loop over opponent vector and remove any elements that are inactive
  for (int i = 0; i < opponent.size(); i++) {
    // if inactive remove
    if (!opponent[i]->GetIsActive()) {
      opponent.erase(opponent.begin() + i);
      i--;
    }
  }

  vector<unique_ptr<OpponentProjectile>>& opponent_projectile =
      GetOpponentProjectiles();
  // Loop over opponent_projectile vector and remove any elements that are
  // inactive
  for (int i = 0; i < opponent_projectile.size(); i++) {
    // if inactive remove
    if (!opponent_projectile[i]->GetIsActive()) {
      opponent_projectile.erase(opponent_projectile.begin() + i);
      i--;
    }
  }

  vector<unique_ptr<PlayerProjectile>>& player_projectile =
      GetPlayerProjectiles();
  // Loop over player_projectile vector and remove any elements that are
  // inactive
  for (int i = 0; i < player_projectile.size(); i++) {
    // if inactive remove
    if (!player_projectile[i]->GetIsActive()) {
      player_projectile.erase(player_projectile.begin() + i);
      i--;
    }
  }
}

void Game::LaunchProjectiles() {
  // Launching Projectiles
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  vector<unique_ptr<OpponentProjectile>>& opponent_projectile =
      GetOpponentProjectiles();
  for (int i = 0; i < opponent.size(); i++) {
    unique_ptr<OpponentProjectile> new_opponent =
        opponent[i]->LaunchProjectile();
    if (new_opponent != nullptr) {
      opponent_projectile.push_back(move(new_opponent));
    }
  }
}

void Game::UpdateScreen() {

  Image& image = GetGameScreen();

  if (!game_started_) {
    for (unsigned int i = 0; i < image.GetHeight(); ++i) {
      for (unsigned int j = 0; j < image.GetWidth(); ++j) {
        Color color = start_screen_.GetColor(j, i);
        image.SetColor(j, i, color);
      }
    }
    image.Flush();
    return;
  }
  
  // Draw Screen white
  DrawBackgroundImage();

  // Intialize vectors objects to loop over
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  vector<unique_ptr<OpponentProjectile>>& opponent_projectile =
      GetOpponentProjectiles();
  Player& player = GetPlayer();
  vector<unique_ptr<PlayerProjectile>>& player_projectile =
      GetPlayerProjectiles();

  // Intialize the color of the text and turn the int score into string
  string scoreToString = std::to_string(score_);
  Color textColor(0, 0, 0);

  // Including the current score of the game
  image.DrawText(5, 5, scoreToString, 20, textColor);
  if (status_) {
    // Loop over opponent vector
    for (int i = 0; i < opponent.size(); i++) {
      if (opponent[i]->GetIsActive() == true) {
        opponent[i]->Draw(image);
      }
    }
    // Loop over opponent projectile vector
    // for (int i = 0; i < opponent_projectile.size(); i++) {
    //   if (opponent_projectile[i]->GetIsActive() == true) {
    //     opponent_projectile[i]->Draw(image);
    //   }
    // }
    // Loop over player projectile vector
    for (int i = 0; i < player_projectile.size(); i++) {
      if (player_projectile[i]->GetIsActive() == true) {
        player_projectile[i]->Draw(image);
      }
    }

    if (player.GetIsActive()) {
      player.Draw(image);
    }
  } else {
    // if the player lost. Display game Screen
    // Get the middle of the screen for height and width.
    int middleOfWidthScreen = (image.GetWidth() / 2) - 100;
    int MiddleHeightOfScreen = (image.GetHeight() / 2) - 25;
    for (int i = 0; i < opponent.size(); i++) {
      if (opponent[i]->GetIsActive() == true) {
        opponent[i]->Draw(image);
      }
    }
    image.DrawText(middleOfWidthScreen, MiddleHeightOfScreen, "Game Over", 50,
                   textColor);
  }
  }

void Game::OnAnimationStep() {
  Image& image = GetGameScreen();
  vector<unique_ptr<Opponent>>& opponent = GetOpponents();
  if (opponent.size() == 0) {
    CreateOpponents();
  }
  
  MoveGameElements();
  // LaunchProjectiles(); // Removing look 
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  image.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent& event) {
    if (!game_started_) {
      int x = event.GetX();
      int y = event.GetY();

      // Check if the mouse click is within the start button coordinates
      if (event.GetMouseAction() == graphics::MouseAction::kPressed &&
          x >= 60 && x <= 185 && y >= 380 && y <= 437) {
        game_started_ = true;
      }

      return;
    }
  
  int x = event.GetX();
  int y = event.GetY();
  Player& player = GetPlayer();

  if (event.GetMouseAction() == graphics::MouseAction::kDragged) {
    if (x < 500 && x >= 0 && y >= 0 && y < 800) {
      player.SetX(x - 10);
      player.SetY(y - 25);
      
    }
  } else if (event.GetMouseAction() == graphics::MouseAction::kMoved) {
    if (x < 500 && x >= 0 && y >= 0 && y < 800) {
      player.SetX(x - 10);
      player.SetY(y - 25);
    }
  } else if (event.GetMouseAction() == graphics::MouseAction::kPressed) {
    if(firedCounter_ != 0) return;
    FirePlayerProjectile(player);
    firedCounter_++;
  }
}

void Game::Start() {
  Image& image = GetGameScreen();
  image.ShowUntilClosed();
}
// ---------------- End of Game Memeber Functions ------------------
// ---------------- End of game Class ------------------------------
