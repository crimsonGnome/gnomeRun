/*
Name: Destiny Bonillas
CWID: 887190072
Email: destinybonillas@csu.fullerton.edu

Name: Joseph Eggers
CWID: 885939488
Email: joseph.eggers@csu.fullerton.edu
*/

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "opponentCharacter_/opponent.h"
#include "playerCharacter_/player.h"

using std::vector, std::unique_ptr;

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 private:
  graphics::Image gameScreen_;
  vector<unique_ptr<Opponent>> opponent_;
  vector<unique_ptr<OpponentProjectile>> opponentProjectile_;
  vector<unique_ptr<PlayerProjectile>> playerProjectile_;
  Player player_;
  int score_ = 0;
  bool status_ = true;

  // Private Function
  void FirePlayerProjectile(Player&);

 public:
  // constructors
  Game();
  Game(int height, int width);

  // Getters (referenced)
  graphics::Image& GetGameScreen() { return gameScreen_; };
  vector<unique_ptr<Opponent>>& GetOpponents() { return opponent_; };
  vector<unique_ptr<OpponentProjectile>>& GetOpponentProjectiles() {
    return opponentProjectile_;
  };
  vector<unique_ptr<PlayerProjectile>>& GetPlayerProjectiles() {
    return playerProjectile_;
  };
  Player& GetPlayer() { return player_; };
  int GetScore() { return score_; };
  bool HasLost() { return !status_; };

  // Memeber Functions
  void CreateOpponents();
  void Init();
  void UpdateScreen();
  void Start();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep();
  void OnMouseEvent(const graphics::MouseEvent& event);
  void RemoveInactive();
  void LaunchProjectiles();
};

#endif
