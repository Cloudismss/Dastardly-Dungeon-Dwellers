#ifndef DASTARDLY_DUNGEON_DWELLERS_SKELETON_H
#define DASTARDLY_DUNGEON_DWELLERS_SKELETON_H

#include "Enemy.h"

class Skeleton : public Enemy
{
public:
  Skeleton(short unsigned int playerLevel) : Enemy(playerLevel)
  {
    name = "Skeleton";
    meleeVulnerability = 2.0;
    magicVulnerability = 1.2;
    rangedVulnerability = 0.5;
  }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_SKELETON_H
