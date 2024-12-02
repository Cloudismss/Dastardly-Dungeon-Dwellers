#ifndef DASTARDLY_DUNGEON_DWELLERS_TROLL_H
#define DASTARDLY_DUNGEON_DWELLERS_TROLL_H

#include "Enemy.h"

class Troll : public Enemy
{
public:
  Troll(short unsigned int playerLevel) : Enemy(playerLevel)
  {
    name = "Troll";
    meleeVulnerability = 1.3;
    magicVulnerability = 0.6;
    rangedVulnerability = 2.0;
  }  
};

#endif // DASTARDLY_DUNGEON_DWELLERS_TROLL_H
