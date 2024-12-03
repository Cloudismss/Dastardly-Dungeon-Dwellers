#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H

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

  // Accessors
  static inline int getProgression() { return enemyProgression; }

private:
  static inline int enemyProgression = 0;
  const static inline vector<int> stage1Baddies = { SKELETON, GOBLIN, ORC };
  const static inline vector<int> stage2Baddies = { TROLL, CYCLOPS };
  const static inline vector<int> stage3Baddies = { MINOTAUR };  

private:
  // Helper functions
  static int calculateLevel();
  static int calculateName();
};

#endif // DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H
