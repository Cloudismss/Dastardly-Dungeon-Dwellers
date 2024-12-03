#include "Orc.h"

Orc::Orc(int playerLevel) : Enemy(playerLevel)
{
  name = "Orc";
  meleeVulnerability = 0.7;
  magicVulnerability = 2.0;
  rangedVulnerability = 1.0;
  announceEnemy();
}
