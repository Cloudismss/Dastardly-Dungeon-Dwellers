#ifndef GAMEART_H
#define GAMEART_H

#include "Player.h"

namespace art
{
  namespace game
  {
    void menu();
    void victory(Player *player);
    void gameOver(Player *player);
  }
}

#endif // GAMEART_H
