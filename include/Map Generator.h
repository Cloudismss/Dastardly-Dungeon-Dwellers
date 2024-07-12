#include <string>

#include "Map.h"

using std::string;

void generateMap(char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition, const int ROW_MIDPOINT, const int COLUMN_MIDPOINT);
void generateMapRoomSpawner(const int ROW_MIDPOINT, const int COLUMN_MIDPOINT, const int ROOM_DISTANCE, const int SIMILAR_DISTANCE, const int ROOMS_ALLOWED, const string &roomName, char roomSymbol, char mapArray[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS]);