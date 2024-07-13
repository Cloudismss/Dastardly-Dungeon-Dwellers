#include "Globals.h"

#include "Map.h"
#include "Room Enemy.h"
#include "Room Exit.h"
#include "Room Loot.h"
#include "Room Merchant.h"

// roomController group, these functions are top-level and handle a majority of the game
void roomController(string &className, int &potionCount, int &armorCount, int &goldCount, int &keyCount, int &roomCount, bool &gameOver, bool &gameVictory, char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition, std::ifstream &characterStats);