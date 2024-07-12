// Troll Class Definitions

void Troll::setEnemyAttributes()
{
  // Temp values
  name = "Troll";
  tier = 1;
  health = 20;
  damage = 5;
  meleeVulnerability = 1.0;
  magicVulnerability = 0.5;
  rangedVulnerability = 2.0;
  attackLow = 5;
  attackHigh = 10;
}

void Troll::announceEnemy()
{
  cout << "PLACEHOLDER: Zoinks! TROLL\n";
}