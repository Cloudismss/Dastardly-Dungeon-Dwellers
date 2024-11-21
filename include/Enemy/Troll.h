#ifndef DASTARDLY_DUNGEON_DWELLERS_TROLL_H
#define DASTARDLY_DUNGEON_DWELLERS_TROLL_H

#include "Enemy.h"

class Troll : public Enemy
{
public:
  // Pass value to base constructor
  Troll(short unsigned int playerProgression) : Enemy(playerProgression) {}
  // OR
  using Enemy::Enemy;

  // Example of redefined function
  void setEnemyLevel(short unsigned int playerProgression)
  {
    level = playerProgression;
    Enemy::setEnemyLevel(level * 5);
  }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_TROLL_H
