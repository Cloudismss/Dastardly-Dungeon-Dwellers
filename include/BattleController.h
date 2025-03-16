#ifndef BATTLECONTROLLER_H
#define BATTLECONTROLLER_H

namespace battle
{
  enum Result
  {
    WIN,
    LOSE,
    RUN
  };
}

#include "Enemy.h"
#include "Player.h"

int battleController(Player *player, Enemy *enemy);

#endif // BATTLECONTROLLER_H
