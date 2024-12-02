#include "Enemy Spawner.h"

#include "Cyclops.h"
#include "Goblin.h"
#include "Minotaur.h"
#include "Orc.h"
#include "Skeleton.h"
#include "Troll.h"

Enemy *EnemySpawner::generateEnemy(short unsigned int playerLevel)
{
  ++enemyProgression;

  short unsigned int name = calculateName();

  switch(name)
  {
    case Cyclops:
      return new Cyclops(playerLevel);
    case Goblin:
      return new Goblin(playerLevel);
    case Minotaur:
      return new Minotaur(playerLevel);
    case Orc:
      return new Orc(playerLevel);
    case Skeleton:
      return new Skeleton(playerLevel);
    case Troll:
      return new Troll(playerLevel);
  }

  return nullptr;
}

int EnemySpawner::calculateName()
{
  int name = Troll;
  return name;
}
