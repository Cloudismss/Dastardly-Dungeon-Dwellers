#include "EnemySpawner.h"

#include <vector>

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
      break;
    case GOBLIN:
      return new Goblin(playerLevel);
      break;
    case MINOTAUR:
      return new Minotaur(playerLevel);
      break;
    case ORC:
      return new Orc(playerLevel);
      break;
    case SKELETON:
      return new Skeleton(playerLevel);
      break;
    case TROLL:
      return new Troll(playerLevel);
      break;
    case BOSS:
      return new Boss(playerLevel);
      break;
    default:
      return nullptr;
  }
}

int EnemySpawner::calculateName()
{
  static std::vector<int> baddies;

  if (Enemy::getProgression() == 0)
    baddies.insert(baddies.end(), stage1Baddies.begin(), stage1Baddies.end());
  else if (Enemy::getProgression() == CHECKPOINT_1)
    baddies.insert(baddies.end(), stage2Baddies.begin(), stage2Baddies.end());
  else if (Enemy::getProgression() == CHECKPOINT_2)
    baddies.insert(baddies.end(), stage3Baddies.begin(), stage3Baddies.end());

  if (Enemy::getProgression() > CHECKPOINT_3 && (1 + rand() % 100) <= 10)
    return BOSS;

  return baddies[rand() % baddies.size()];
}
