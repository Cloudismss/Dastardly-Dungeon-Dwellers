#include "Skeleton.h"

Skeleton::Skeleton(int playerLevel) : Enemy(playerLevel)
{
  name = "Skeleton";
  meleeVulnerability = 2.0;
  magicVulnerability = 1.2;
  rangedVulnerability = 0.5;
  announceEnemy();
}
