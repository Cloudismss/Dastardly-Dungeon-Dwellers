#include "Troll.h"

Troll::Troll(int playerLevel) : Enemy(playerLevel)
{
  name = "Troll";
  meleeVulnerability = 1.3;
  magicVulnerability = 0.6;
  rangedVulnerability = 2.0;
  announceEnemy();
}
