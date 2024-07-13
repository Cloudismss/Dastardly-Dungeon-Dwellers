#include <iostream>
#include <string>

#include "Art.h"
#include "Room Enemy.h"
#include "Validation.h"

using std::cin;
using std::cout;
using std::string;

bool roomLoot(string &className, int &potionCount, int armorCount, int &goldCount, int &keyCount, int enemyProgression, bool &isEnemyRoom, std::ifstream &characterStats);