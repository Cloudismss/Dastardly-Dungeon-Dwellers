#ifndef DASTARDLY_DUNGEON_DWELLERS_GOBLIN_H
#define DASTARDLY_DUNGEON_DWELLERS_GOBLIN_H

#include "Enemy.h"

class Goblin : public Enemy
{
public:
  Goblin(short unsigned int playerLevel) : Enemy(playerLevel)
  {
    name = "Goblin";
    meleeVulnerability = 1.3;
    magicVulnerability = 1.0;
    rangedVulnerability = 1.4;  
  }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_GOBLIN_H
