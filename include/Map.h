#ifndef MAP_H
#define MAP_H

#include <string>

const int ROWS = 9;
const int COLS = 9;

const int ROW_MIDPOINT = ROWS / 2;
const int COL_MIDPOINT = COLS / 2;

class Position
{
public:
  char symbol;
  bool explored;
  std::string contents;
  Position()
  {
    symbol = ' ';
    explored = false;
  }
};

class Map
{
public:
  Map();
  ~Map() { }

private:
  // Helper Functions
  void generateMap();
  void generateRooms(const std::string &ROOM_NAME, char ROOM_SYMBOL, int ROOM_DISTANCE, int DUPE_DISTANCE, int ROOMS_ALLOWED);
  void mapPrint() const;
  void mapMovement();

public:
  bool move();
  std::string getRoomContents() const { return position[rowPos][colPos].contents; }

private:
  Position position[ROWS][COLS];
  int rowPos;
  int colPos;
};

#endif // MAP_H
