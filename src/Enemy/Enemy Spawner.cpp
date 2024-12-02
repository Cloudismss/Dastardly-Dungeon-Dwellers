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
    case CYCLOPS:
      return new Cyclops(playerLevel);
    case GOBLIN:
      return new Goblin(playerLevel);
    case MINOTAUR:
      return new Minotaur(playerLevel);
    case ORC:
      return new Orc(playerLevel);
    case SKELETON:
      return new Skeleton(playerLevel);
    case TROLL:
      return new Troll(playerLevel);
    default:
      return nullptr;
  }
}

int EnemySpawner::calculateName()
{
  return TROLL;
}
