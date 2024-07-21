#ifndef DASTARDLY_DUNGEON_DWELLERS_MAP_H
#define DASTARDLY_DUNGEON_DWELLERS_MAP_H

#include <string>

using std::string;

// Map Constants - feel free to change - have to both be odd numbers or positioning will be weird
const int MAP_ROWS = 9;
const int MAP_COLUMNS = 9;

class Map
{
public:
  Map();
  ~Map();

private:
  const int ROW_MIDPOINT = MAP_ROWS / 2;
  const int COLUMN_MIDPOINT = MAP_COLUMNS / 2;
  char *mapArray[MAP_ROWS][MAP_COLUMNS];
  bool *roomExplored[MAP_ROWS][MAP_COLUMNS];
  string *roomContents[MAP_ROWS][MAP_COLUMNS];
  static int rowPosition;
  static int columnPosition;
  static char *previousPlayerPosition;

  void generateMap();
  void generateRooms(const string &ROOM_NAME, const char ROOM_SYMBOL, const int ROOM_DISTANCE, const int SIMILAR_DISTANCE, const int ROOMS_ALLOWED);
  void mapPrint();
  void mapMovement();

public:
  bool move();
  string getRoomContents() { return *roomContents[rowPosition][columnPosition]; }
};

#endif //DASTARDLY_DUNGEON_DWELLERS_MAP_H