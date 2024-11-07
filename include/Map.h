#ifndef DASTARDLY_DUNGEON_DWELLERS_MAP_H
#define DASTARDLY_DUNGEON_DWELLERS_MAP_H

#include <string>

using std::string;

// Map Constants - feel free to change - have to both be odd numbers or positioning will be weird
const int ROWS = 9;
const int COLS = 9;
// Map Midpoints
const int ROW_MIDPOINT = ROWS / 2;
const int COL_MIDPOINT = COLS / 2;

class Position
{
public:
  char symbol;
  bool explored;
  string contents;
  Position() { symbol = ' '; explored = false; contents = " "; }
};

class Map
{
private:
  Position position[ROWS][COLS];
  int rowPos;
  int colPos;

  void generateMap();
  void generateRooms(const string &ROOM_NAME, const char ROOM_SYMBOL, const int ROOM_DISTANCE, const int DUPE_DISTANCE, const int ROOMS_ALLOWED);
  void mapPrint();
  void mapMovement();
public:
  Map();
  ~Map() { }

  // Functions
  bool move();
  string getRoomContents() const { return position[rowPos][colPos].contents; }
};

#endif //DASTARDLY_DUNGEON_DWELLERS_MAP_H
