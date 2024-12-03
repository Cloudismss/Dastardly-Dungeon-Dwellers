#include "Cyclops.h"

Cyclops::Cyclops(int playerLevel) : Enemy(playerLevel)
{
  name = "Cyclops";
  meleeVulnerability = 1.0;
  magicVulnerability = 1.0;
  rangedVulnerability = 1.0;
  announceEnemy();
}
