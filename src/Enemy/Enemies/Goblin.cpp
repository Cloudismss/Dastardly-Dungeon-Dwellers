#include "Goblin.h"

Goblin::Goblin(int playerLevel) : Enemy(playerLevel)
{
  name = "Goblin";
  meleeVulnerability = 1.3;
  magicVulnerability = 1.0;
  rangedVulnerability = 1.4;
  announceEnemy();
}
  