#ifndef DASTARDLY_DUNGEON_DWELLERS_ROOM_CONTROLLER_H
#define DASTARDLY_DUNGEON_DWELLERS_ROOM_CONTROLLER_H

#include "Globals.h"

#include "Map.h"
#include "Room Enemy.h"
#include "Room Exit.h"
#include "Room Loot.h"
#include "Room Merchant.h"

// roomController group, these functions are top-level and handle a majority of the game
void roomController(string &className, int &potionCount, int &armorCount, int &goldCount, int &keyCount, int &roomCount, bool &gameOver, bool &gameVictory, Map *map, std::ifstream &characterStats);

#endif //DASTARDLY_DUNGEON_DWELLERS_ROOM_CONTROLLER_H