#ifndef DASTARDLY_DUNGEON_DWELLERS_TROLL_H
#define DASTARDLY_DUNGEON_DWELLERS_TROLL_H

#include "Enemy.h"

class Troll : public Enemy
{
public:
  // Pass value to base constructor
  Troll(int playerProgression) : Enemy(playerProgression) {}
  // OR
  using Enemy::Enemy;

  // Example of redefined function
  void setEnemyTier(int playerProgression)
  {
    tier = playerProgression;
    Enemy::setEnemyTier(tier * 5);
  }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_TROLL_H
