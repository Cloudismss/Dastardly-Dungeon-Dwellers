#ifndef DASTARDLY_DUNGEON_DWELLERS_ROOM_LOOT_H
#define DASTARDLY_DUNGEON_DWELLERS_ROOM_LOOT_H

#include <iostream>
#include <string>

#include "Art.h"
#include "Room Enemy.h"
#include "Validation.h"

using std::cin;
using std::cout;
using std::string;

bool roomLoot(Player *player, bool &isEnemyRoom);

#endif //DASTARDLY_DUNGEON_DWELLERS_ROOM_LOOT_H