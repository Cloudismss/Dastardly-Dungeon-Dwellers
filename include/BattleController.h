#ifndef DASTARDLY_DUNGEON_DWELLERS_BATTLE_CONTROLLER_H
#define DASTARDLY_DUNGEON_DWELLERS_BATTLE_CONTROLLER_H

#include "Enemy.h"
#include "Player.h"

enum Result
{
  WIN,
  LOSE,
  RUN
};

int battleController(Player *player, Enemy *enemy);

#endif // DASTARDLY_DUNGEON_DWELLERS_BATTLE_CONTROLLER_H
