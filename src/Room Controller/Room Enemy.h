#ifndef DASTARDLY_DUNGEON_DWELLERS_ROOM_ENEMY_H
#define DASTARDLY_DUNGEON_DWELLERS_ROOM_ENEMY_H

#include <iostream>
#include <string>

#include "Battle Controller.h"

using std::string;

bool roomEnemy(string &className, int &potionCount, int armorCount, int &goldCount, int &keyCount, int enemyProgression, std::ifstream &characterStats);

#endif //DASTARDLY_DUNGEON_DWELLERS_ROOM_ENEMY_H