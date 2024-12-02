#ifndef DASTARDLY_DUNGEON_DWELLERS_ORC_H
#define DASTARDLY_DUNGEON_DWELLERS_ORC_H

#include "Enemy.h"

class Orc : public Enemy
{
public:
  Orc(short unsigned int playerLevel) : Enemy(playerLevel)
  {
    name = "Orc";
    meleeVulnerability = 0.7;
    magicVulnerability = 2.0;
    rangedVulnerability = 1.0;      
  }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_ORC_H
