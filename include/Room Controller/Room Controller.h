#ifndef DASTARDLY_DUNGEON_DWELLERS_ROOM_CONTROLLER_H
#define DASTARDLY_DUNGEON_DWELLERS_ROOM_CONTROLLER_H

#include "Map.h"
#include "Player.h"

// roomController group, these functions are top-level and handle a majority of the game
void roomController(Player *player, Map *map, bool &gameOver, bool &gameVictory);

#endif //DASTARDLY_DUNGEON_DWELLERS_ROOM_CONTROLLER_H