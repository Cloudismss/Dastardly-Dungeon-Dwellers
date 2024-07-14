#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_DAMAGE_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_DAMAGE_H

#include <iostream>
#include <string>

#include "Globals.h"

using std::cout;
using std::string;

float enemyDamage(int enemyTier, const string &enemyName, bool boss, int armorCount);

#endif //DASTARDLY_DUNGEON_DWELLERS_ENEMY_DAMAGE_H