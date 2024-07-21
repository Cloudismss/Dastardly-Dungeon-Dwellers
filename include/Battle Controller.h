#ifndef DASTARDLY_DUNGEON_DWELLERS_BATTLE_CONTROLLER_H
#define DASTARDLY_DUNGEON_DWELLERS_BATTLE_CONTROLLER_H

#include <string>

#include "Art.h"
#include "Enemy.h"
#include "Player.h"
#include "Skills.h"
#include "Validation.h"

using std::string;

int battleController(Player *player, Enemy *enemy);

#endif //DASTARDLY_DUNGEON_DWELLERS_BATTLE_CONTROLLER_H