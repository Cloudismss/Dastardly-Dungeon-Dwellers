#ifndef DASTARDLY_DUNGEON_DWELLERS_CYCLOPS_H
#define DASTARDLY_DUNGEON_DWELLERS_CYCLOPS_H

#include "Enemy.h"

class Cyclops : public Enemy
{
public:
  Cyclops(short unsigned int playerLevel) : Enemy(playerLevel)
  {
    name = "Cyclops";
    meleeVulnerability = 1.0;
    magicVulnerability = 1.0;
    rangedVulnerability = 1.0;  
  }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_CYCLOPS_H
