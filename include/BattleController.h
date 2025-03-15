#ifndef BATTLECONTROLLER_H
#define BATTLECONTROLLER_H

#include "Enemy.h"
#include "Player.h"

enum Result
{
  WIN,
  LOSE,
  RUN
};

int battleController(Player *player, Enemy *enemy);

#endif // BATTLECONTROLLER_H
