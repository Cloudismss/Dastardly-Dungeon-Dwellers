#include "Minotaur.h"

Minotaur::Minotaur(int playerLevel) : Enemy(playerLevel)
{
  name = "Minotaur";
  meleeVulnerability = 1.4;
  magicVulnerability = 1.3;
  rangedVulnerability = 0.8;
  announceEnemy();
}
