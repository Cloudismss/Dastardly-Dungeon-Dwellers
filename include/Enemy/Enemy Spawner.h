#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H

#include "Enemy.h"

class EnemySpawner
{
public:
  // Return random new enemy
  static Enemy *generateEnemy(short unsigned int playerLevel);

  // Acessors
  static inline short unsigned int getProgression() { return enemyProgression; }
  static inline vector<string> getStage1Baddies() { return stage1Baddies; }
  static inline vector<string> getStage2Baddies() { return stage2Baddies; }
  static inline vector<string> getStage3Baddies() { return stage3Baddies; }

private:
  static inline short unsigned int enemyProgression = 0;
  const static inline vector<string> stage1Baddies = {"Goblin", "Orc", "Skeleton"};
  const static inline vector<string> stage2Baddies = {"Troll", "Cyclops"};
  const static inline vector<string> stage3Baddies = {"Minotaur"};  

private:
  // Helper functions
  static short unsigned int calculateLevel();
  static string calculateName();
};

#endif // DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H