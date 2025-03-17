#include "Map.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "Game.h"
#include "Validation.h"

Map::Map()
{
  // Position Tracking Variables
  rowPos = ROWS / 2;
  colPos = COLS / 2;

  // Generate map
  generateMap();
}

void Map::mapPrint() const
{
  // Prints the map
  std::cout << std::setfill('-') << std::setw(64) << " " << std::setfill(' ');
  std::cout << "\n\n";
  std::cout << "MAP SELECTION" << "\n\n";
  std::cout << "You are here [*]\n";
  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLS; ++j)
      std::cout << "[" << position[i][j].symbol << "]" ;
    std::cout << "\n";
  }

  // DEBUG OPTION - prints additional helpful debug maps
  if (Game::getDebug())
  {
    std::cout << "\n";
    std::cout << std::setfill('-') << std::setw(64) << " " << std::setfill(' ');
    std::cout << "\n\n";
    std::cout << std::setw(65/2) << "DEBUG MAPS" << "\n\n";
    for (int i = 0; i < ROWS; ++i)
    {
      for (int j = 0; j < COLS; ++j)
        std::cout << "[" << position[i][j].explored << "]" ;
      std::cout << "\n";
    }
    std::cout << "\n";
    for (int i = 0; i < ROWS; ++i)
    {
      for (int j = 0; j < COLS; ++j)
        std::cout << "[" << position[i][j].contents << "]" ;
      std::cout << "\n";
    }
    std::cout << "\n" << std::setfill('-') << std::setw(64) << " " << std::setfill(' ');
    std::cout << "\n";
  }
  std::cout << "\n";
}

bool Map::move()
{
   // Prints the map
  mapPrint();

  // Overwrite current position symbol before moving
  if (!(position[rowPos][colPos].contents == "Merchant" || position[rowPos][colPos].contents == "Exit"))
    position[rowPos][colPos].symbol = 'o'; // Place a 'o' value in position's symbol element to indicate a previously cleared room
  else if (position[rowPos][colPos].contents == "Merchant")
    position[rowPos][colPos].symbol = '$'; // Place a '$' value in position's symbol element to indicate a discovered merchant shop
  else if (position[rowPos][colPos].contents == "Exit")
    position[rowPos][colPos].symbol = '#'; // Place a '#' value in position's symbol element to indicate the exit

  // Adjusts either rowPos or colPos by 1 or -1 based on direction choice by the user
  mapMovement();

  // Check if we've been in this room before
  bool roomCleared = false;
  if (position[rowPos][colPos].explored)
    roomCleared = true;
  else
    position[rowPos][colPos].explored = true; // Set the current index to true, since we'll be clearing this room next

  // Place new value in player's new position
  position[rowPos][colPos].symbol = '*';

  // Prints the map
  mapPrint();

  // Print map divider
  std::cout << std::setfill('-') << std::setw(64) << " " << std::setfill(' ') << "\n\n";

  // If the room was already visited, return true, if not, return false
  return roomCleared;
}

void Map::mapMovement()
{
  bool loopFlag = true;
  char directionChoice = ' ';
  do
  {
    // Accept direction from user, validates that the direction is within map bounds
    std::cout << "Which direction would you like to go? (N|E|S|W): ";
    std::cin >> directionChoice;
    std::cout << "\n";
    if (validate::direction(rowPos, colPos, directionChoice, ROWS, COLS))
      loopFlag = false;
  } while (loopFlag);

  // Adjust row and column values based on user choice
  switch (directionChoice)
  {
    case 'N':
    {
      --rowPos;
      break;
    }
    case 'S':
    {
      ++rowPos;
      break;
    }
    case 'E':
    {
      ++colPos;
      break;
    }
    case 'W':
    {
      --colPos;
      break;
    }
  }
}

void Map::generateMap()
{
  // Place the player icon in the starter room and sets the starter room to "explored" with "Start" contents
  position[ROW_MIDPOINT][COL_MIDPOINT].symbol = '*';
  position[ROW_MIDPOINT][COL_MIDPOINT].explored = true;
  position[ROW_MIDPOINT][COL_MIDPOINT].contents = "Start";

  // Spawn an exit on the map
  const int MIN_EXIT_DISTANCE = 3; // The exit must spawn 3 tiles away from the center
  bool validExitSpawns[ROWS][COLS] = {0}; // This array finds a valid spawn location based on distance from spawn
  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLS; ++j)
    {
      if ((i <= ROW_MIDPOINT - MIN_EXIT_DISTANCE || i >= ROW_MIDPOINT + MIN_EXIT_DISTANCE) || (j <= COL_MIDPOINT - MIN_EXIT_DISTANCE || j >= COL_MIDPOINT + MIN_EXIT_DISTANCE))
        validExitSpawns[i][j] = true;
    }
  }
  bool exitPlaced = false;
  do
  {
    int randomRow = rand() % ROWS;
    int randomColumn = rand() % COLS;
    if (validExitSpawns[randomRow][randomColumn])
    {
      position[randomRow][randomColumn].symbol = '#';
      position[randomRow][randomColumn].contents = "Exit";
      exitPlaced = true;
    }
  } while (!exitPlaced);

  // Spawn Merchants
  const int MERCHANT_ROOMS_DISTANCE = 2; // Merchants must spawn 2 tiles away from the center
  const int MERCHANT_ROOMS_DUPE_DISTANCE = 1; // Merchants rooms must spawn 1 tile away from each other
  const int MERCHANT_ROOMS_ALLOWED = ROWS / 2 + 1; // Number of merchants to spawn is based on map size
  const std::string MERCHANT_ROOMS_NAME = "Merchant";
  const char MERCHANT_SYMBOL = '$';
  generateRooms(MERCHANT_ROOMS_NAME, MERCHANT_SYMBOL, MERCHANT_ROOMS_DISTANCE, MERCHANT_ROOMS_DUPE_DISTANCE, MERCHANT_ROOMS_ALLOWED);

  // Calculate Remaining Non-Enemy Rooms
  int REMAINING_ROOMS_DISTANCE = 2; // Non-enemy rooms must spawn 2 tiles away from the center, this is so the first room is guaranteed to contain an enemy
  int REMAINING_ROOMS_DUPE_DISTANCE = 1; // Non-enemy rooms must spawn 1 tiles away from each other
  int REMAINING_ROOMS_ALLOWED = (ROWS * COLS) - 2 - MERCHANT_ROOMS_ALLOWED; // The literal 2 is for 1 exit and 1 spawn location

  // Spawn Loot Room
  const int LOOT_ROOMS_ALLOWED = REMAINING_ROOMS_ALLOWED * 0.15f; // 15% of remaining rooms can be loot rooms
  const std::string LOOT_ROOMS_NAME = "Loot";
  const char LOOT_ROOMS_SYMBOL = 'L';
  generateRooms(LOOT_ROOMS_NAME, LOOT_ROOMS_SYMBOL, REMAINING_ROOMS_DISTANCE, REMAINING_ROOMS_DUPE_DISTANCE, LOOT_ROOMS_ALLOWED);

  // Spawn Enemy Rooms
  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLS; ++j)
    {
      if (position[i][j].contents == " ")
      {
        position[i][j].contents = "Enemy";
        if (Game::getDebug())
          position[i][j].symbol = 'E';
      }
    }
  }
}

void Map::generateRooms(const std::string &ROOM_NAME, char ROOM_SYMBOL, int ROOM_DISTANCE, int DUPE_DISTANCE, int ROOMS_ALLOWED)
{
  bool validSpawns[ROWS][COLS] = {0}; // This array finds valid spawn locations based on distance from spawn and other from other spawns in this function
  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLS; ++j)
      // Mark the room as valid if the room is empty and a valid distance away from spawn
      if (position[i][j].contents == " " && (i <= ROW_MIDPOINT - ROOM_DISTANCE || i >= ROW_MIDPOINT + ROOM_DISTANCE) || (j <= COL_MIDPOINT - ROOM_DISTANCE || j >= COL_MIDPOINT + ROOM_DISTANCE))
        validSpawns[i][j] = true;
  }

  // Using these variable to make sure the function has a way out if it can't find a spawn after x attempts
  int spawnAttempts = 0;
  int allowedAttempts = 10;
  if (ROOM_NAME == "Merchant")
    allowedAttempts = 100; // I want to ensure the proper amount of merchants are always spawned

  int roomsPlaced = 0;
  do
  {
    // Select a random location
    int randomRow = rand() % ROWS;
    int randomColumn = rand() % COLS;

    // Check to make sure the room is valid and empty before spawning the room
    if (validSpawns[randomRow][randomColumn] && position[randomRow][randomColumn].contents == " ")
    {
      // Place room
      position[randomRow][randomColumn].contents = ROOM_NAME;
      validSpawns[randomRow][randomColumn] = false;
      ++roomsPlaced;

      // DEBUG Option - Print loot room icons on map
      if (Game::getDebug())
        position[randomRow][randomColumn].symbol = ROOM_SYMBOL;

      // Mark spaces DUPE_DISTANCE tile(s) away as invalid spawns, so rooms don't spawn too close to each other - if branches check bounds so I don't assign an out of bounds value
      // TODO: num merchants not always correct
      if (randomRow + DUPE_DISTANCE < ROWS)
      {
        validSpawns[randomRow + DUPE_DISTANCE][randomColumn] = false;
        if (randomColumn + DUPE_DISTANCE < COLS)
          validSpawns[randomRow + DUPE_DISTANCE][randomColumn + DUPE_DISTANCE] = false;
        if (randomColumn - DUPE_DISTANCE >= 0)
          validSpawns[randomRow + DUPE_DISTANCE][randomColumn - DUPE_DISTANCE] = false;
      }

      if (randomRow - DUPE_DISTANCE >= 0)
      {
        validSpawns[randomRow - DUPE_DISTANCE][randomColumn] = false;
        if (randomColumn - DUPE_DISTANCE >= 0)
          validSpawns[randomRow - DUPE_DISTANCE][randomColumn - DUPE_DISTANCE] = false;
        if (randomColumn + DUPE_DISTANCE < COLS)
          validSpawns[randomRow - DUPE_DISTANCE][randomColumn + DUPE_DISTANCE] = false;
      }

      if (randomColumn + DUPE_DISTANCE < COLS)
        validSpawns[randomRow][randomColumn + DUPE_DISTANCE] = false;
      if (randomColumn - DUPE_DISTANCE >= 0)
        validSpawns[randomRow][randomColumn - DUPE_DISTANCE] = false;
    }

    // Fallback exit if the spawning luck is poor
    else
      ++spawnAttempts;
  } while (roomsPlaced < ROOMS_ALLOWED && spawnAttempts < allowedAttempts);
}
