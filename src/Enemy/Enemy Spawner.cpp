#include "Enemy Spawner.h"

#include "Troll.h"

Enemy *EnemySpawner::generateEnemy(short unsigned int playerLevel)
{
  ++enemyProgression;

  string name = calculateName();

  if (name == "Troll")
    return new Troll;

  return nullptr;
}

string EnemySpawner::calculateName()
{
  string name = " ";
  return name;
}