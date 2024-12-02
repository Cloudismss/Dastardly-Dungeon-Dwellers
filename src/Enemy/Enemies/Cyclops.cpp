#include "Cyclops.h"

Cyclops::Cyclops(short unsigned int playerLevel) : Enemy(playerLevel)
{
  name = "Cyclops";
  meleeVulnerability = 1.0;
  magicVulnerability = 1.0;
  rangedVulnerability = 1.0;  
}
