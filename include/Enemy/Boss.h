#ifndef DASTARDLY_DUNGEON_DWELLERS_BOSS_H
#define DASTARDLY_DUNGEON_DWELLERS_BOSS_H

#include "Enemy.h"

class Boss: public Enemy
{
  void setEnemyAttributes() override;
};

#endif //DASTARDLY_DUNGEON_DWELLERS_BOSS_H