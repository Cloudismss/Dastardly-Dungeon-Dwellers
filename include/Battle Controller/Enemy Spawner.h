#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H

#include <iostream>
#include <string>

#include "Globals.h"

using std::cout;
using std::string;

void battleEnemySpawner(int &enemyTier, int &rewardTier, int &enemyHealth, string &enemyName, int enemyProgression, bool &boss);

#endif //DASTARDLY_DUNGEON_DWELLERS_ENEMY_SPAWNER_H