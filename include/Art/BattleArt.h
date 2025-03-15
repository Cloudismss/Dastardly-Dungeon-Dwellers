#ifndef BATTLEART_H
#define BATTLEART_H

#include "Enemy.h"
#include "Player.h"

namespace art
{
  namespace battle
  {
    enum battleSelections
    {
      HELP = 0,
      MELEE = 1,
      MAGIC = 2,
      RANGED = 3,
      HEAL = 4,
      RUN = 5,
      SWITCH = 6
    };
    
    int menu(Player *player, Enemy *enemy);
    void displayHealth(const string &className, int playerHealth, const string &enemyName, int enemyHealth);
  }
}

#endif // BATTLEART_H
