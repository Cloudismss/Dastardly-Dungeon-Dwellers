#include "Enemy.h"

// Enemy Class Definitions

void Enemy::setEnemyAttributes()
{
  std::cerr << "Error: This text should be overwritten\n";
}

void Enemy::attackEnemy(float attackDamage, const string &attackType)
{
  float resistance = 0;
  if (attackType == "melee")
  {
    resistance = meleeVulnerability;
  }
  else if (attackType == "magic")
  {
    resistance = magicVulnerability;
  }
  else if (attackType == "ranged")
  {
    resistance = rangedVulnerability;
  }
  health -= attackDamage * resistance;
  if (health < 0)
  {
    health = 0;
  }
}

void Enemy::announceEnemy()
{
  std::cerr << "ERROR: This text should be overwritten!\n";
}

void Enemy::debugPrint()
{
  cout << "Name: " << name << "\n"
       << "Tier: " << tier << "\n"
       << "Health: " << health << "\n"
       << "Damage: " << damage << "\n"
       << "Weakness to melee: " << meleeVulnerability << "\n"
       << "Weakness to magic: " << magicVulnerability << "\n"
       << "Weakness to ranged: " << rangedVulnerability << "\n"
       << "Attack range: " << attackLow << "-" << attackHigh << "\n";
}