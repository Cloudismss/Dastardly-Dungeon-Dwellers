#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Enemy.h"

enum EnemyName
{
  CYCLOPS,
  GOBLIN,
  MINOTAUR,
  ORC,
  SKELETON,
  TROLL,
  BOSS
};

class EnemySpawner
{
public:
  // Return random new enemy
  static Enemy *generateEnemy(int playerLevel);

private:
  const static inline vector<int> stage1Baddies = { SKELETON, GOBLIN, ORC };
  const static inline vector<int> stage2Baddies = { TROLL, CYCLOPS };
  const static inline vector<int> stage3Baddies = { MINOTAUR };  

private:
  // Helper functions
  static int calculateLevel();
  static int calculateName();
};

#endif // ENEMYSPAWNER_H
