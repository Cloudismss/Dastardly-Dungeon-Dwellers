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

// Boss Class Definitions

void Boss::setEnemyAttributes()
{
  // Temp values
  name = "Varied Boss Names";
  tier = 10;
  health = 200;
  damage = 50;
  meleeVulnerability = 1.0;
  magicVulnerability = 0.5;
  rangedVulnerability = 2.0;
  attackLow = 10;
  attackHigh = 20;
}

void Boss::announceEnemy()
{
  cout << "PLACEHOLDER: Zoinks! BOSS\n";
}

// Heap Testing Example
void exampleClassInHeap()
{
  // Initialize pointer to a new location on the heap
  Enemy *enemy = new Enemy;

  // How to access member attributes - () ensure the ptr is de-referenced before the member attributes
  (*enemy).getName();
  (*enemy).attackEnemy(10, "melee");

  // Another method to access member attributes
  enemy->getHealth();

  // Note: the 'new' operator calls the constructor for the class and 'delete' calls the destructor

  delete enemy;
}