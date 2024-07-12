#include <string>

using std::string;

// Map Constants - feel free to change - have to both be odd numbers or positioning will be weird
const int MAP_ROWS = 9;
const int MAP_COLUMNS = 9;

// Map Functions
bool map(char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition);
void mapMovement(int &rowPosition, int &columnPosition);