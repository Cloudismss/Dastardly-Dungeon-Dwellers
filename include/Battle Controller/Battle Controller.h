#ifndef DASTARDLY_DUNGEON_DWELLERS_BATTLE_CONTROLLER_H
#define DASTARDLY_DUNGEON_DWELLERS_BATTLE_CONTROLLER_H

#include <string>

#include "Art.h"
#include "Enemy Damage.h"
#include "Enemy Spawner.h"
#include "Player Damage.h"
#include "Player.h"
#include "Skills.h"
#include "Validation.h"

using std::string;

// battleController group, these functions handle all battle related functions. Called within roomController group
int battleController(const string &className, int &rewardTier, int &potionCount, int armorCount, int enemyProgression, std::ifstream &characterStats);
int battleMenu(string &meleeName, string &magicName, string &rangedName, int playerHealth, int enemyHealth);

#endif //DASTARDLY_DUNGEON_DWELLERS_BATTLE_CONTROLLER_H