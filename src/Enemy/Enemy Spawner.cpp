#include "Enemy Spawner.h"

#include "Globals.h"

#include "Boss.h"
#include "Cyclops.h"
#include "Goblin.h"
#include "Minotaur.h"
#include "Orc.h"
#include "Skeleton.h"
#include "Troll.h"

Enemy *EnemySpawner::generateEnemy(int playerLevel)
{
  int name = calculateName();
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
    case BOSS:
      return new Boss(playerLevel);
    default:
      return nullptr;
  }

  ++enemyProgression;
}

int EnemySpawner::calculateName()
{
  static vector<int> baddies;

  if (enemyProgression == 0)
    baddies.insert(baddies.end(), stage1Baddies.begin(), stage1Baddies.end());
  else if (enemyProgression == CHECKPOINT_1)
    baddies.insert(baddies.end(), stage2Baddies.begin(), stage2Baddies.end());
  else if (enemyProgression == CHECKPOINT_2)
    baddies.insert(baddies.end(), stage3Baddies.begin(), stage3Baddies.end());

  if (enemyProgression > CHECKPOINT_3 && (1 + rand() % 100) <= 10)
    return BOSS;

  return baddies[rand() % baddies.size()];
}
