#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H

#include "Enemy.h"

enum EnemyName
{
  Cyclops,
  Goblin,
  Minotaur,
  Orc,
  Skeleton,
  Troll
};

class EnemySpawner
{
public:
  // Return random new enemy
  static Enemy *generateEnemy(short unsigned int playerLevel);

  // Acessors
  static inline short unsigned int getProgression() { return enemyProgression; }
  static inline vector<int> getStage1Baddies() { return stage1Baddies; }
  static inline vector<int> getStage2Baddies() { return stage2Baddies; }
  static inline vector<int> getStage3Baddies() { return stage3Baddies; }

private:
  static inline short unsigned int enemyProgression = 0;
  const static inline vector<int> stage1Baddies = { Skeleton, Goblin, Orc };
  const static inline vector<int> stage2Baddies = { Troll, Cyclops };
  const static inline vector<int> stage3Baddies = { Minotaur };  

private:
  // Helper functions
  static short unsigned int calculateLevel();
  static int calculateName();
};

#endif // DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H
