#include <iomanip>
#include <iostream>
#include <string>

#include "Globals.h"

#include "Validation.h"

using std::cin;
using std::cout;
using std::setfill;
using std::setw;
using std::string;

// Map Functions
bool map(char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition);
void mapMovement(int &rowPosition, int &columnPosition);