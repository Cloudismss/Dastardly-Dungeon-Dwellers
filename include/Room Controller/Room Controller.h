#ifndef DASTARDLY_DUNGEON_DWELLERS_ROOM_CONTROLLER_H
#define DASTARDLY_DUNGEON_DWELLERS_ROOM_CONTROLLER_H

#include "Globals.h"

#include "Map.h"
#include "Player.h"
#include "Room Enemy.h"
#include "Room Exit.h"
#include "Room Loot.h"
#include "Room Merchant.h"

// roomController group, these functions are top-level and handle a majority of the game
void roomController(Player *player, Map *map, bool &gameOver, bool &gameVictory);

#endif //DASTARDLY_DUNGEON_DWELLERS_ROOM_CONTROLLER_H