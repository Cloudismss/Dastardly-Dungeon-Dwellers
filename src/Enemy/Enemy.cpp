#include "Enemy.h"

// Enemy Class Definitions
Enemy::Enemy()
{
  name = generateEnemy();
}

Enemy::~Enemy()
{

}

void Enemy::setEnemyAttributes()
{
  std::cerr << "Error: This text should be overwritten\n";
}

string Enemy::generateEnemy()
{
  std::vector<string> baddies = {"Goblin", "Orc", "Skeleton", "Troll", "Cyclops", "Minotaur"};
  return baddies[1 + (rand() % baddies.size())];
}

void Enemy::receive(double healthAdjust, const string &attackType)
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
  health -= healthAdjust * resistance;
  if (health < 0)
  {
    health = 0;
  }
}

// TODO varied dialogue implementation
void Enemy::announceEnemy()
{
  std::cout << "Yikes! A tier " << tier << " " << name << " has appeared {PLACEHOLDER}\n";
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