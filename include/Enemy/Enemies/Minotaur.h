#ifndef DASTARDLY_DUNGEON_DWELLERS_MINOTAUR_H
#define DASTARDLY_DUNGEON_DWELLERS_MINOTAUR_H

#include "Enemy.h"

class Minotaur : public Enemy
{
public:
  Minotaur(short unsigned int playerLevel) : Enemy(playerLevel)
  {
    name = "Minotaur";
    meleeVulnerability = 1.4;
    magicVulnerability = 1.3;
    rangedVulnerability = 0.8;
  }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_MINOTAUR_H
