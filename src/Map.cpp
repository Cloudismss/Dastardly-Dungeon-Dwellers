#include "Map.h"

#include <iomanip>
#include <iostream>

#include "Validation.h"

using std::cin;
using std::cout;
using std::setfill;
using std::setw;

// Prec=ondition: called to construct a map object
// Post=condition: constructs a map object and initializes default values with a randomly generated map
Map::Map()
{
  // Initialize all the arrays
  for (int i = 0; i < MAP_ROWS; ++i)
  {
      for (int j = 0; j < MAP_COLUMNS; ++j)
      {
          mapArray[i][j] = ' ';
          roomExplored[i][j] = false;
          roomContents[i][j] = " ";
      }
  }

  // Position Tracking Variables
  rowPosition = MAP_ROWS / 2;
  columnPosition = MAP_COLUMNS / 2;

  // Generate map
  generateMap();
}

// Prec=ondition: called to print the map
// Post=condition: prints the map, extra debug information is available
void Map::mapPrint()
{
  // Prints the map
  cout << setfill('-') << setw(64) << " " << setfill(' ');
  cout << "\n\n";
  cout << "MAP SELECTION" << "\n\n";
  cout << "You are here [*]\n";
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
      cout << "[" << mapArray[i][j] << "]" ;
    cout << "\n";
  }

  // DEBUG OPTION - prints other array maps
  if (debug)
  {
    cout << "\n";
    cout << setfill('-') << setw(64) << " " << setfill(' ');
    cout << "\n\n";
    cout << setw(65/2) << "DEBUG MAPS" << "\n\n";
    for (int i = 0; i < MAP_ROWS; ++i)
    {
      for (int j = 0; j < MAP_COLUMNS; ++j)
        cout << "[" << roomExplored[i][j] << "]" ;
      cout << "\n";
    }
    cout << "\n";
    for (int i = 0; i < MAP_ROWS; ++i)
    {
      for (int j = 0; j < MAP_COLUMNS; ++j)
        cout << "[" << roomContents[i][j] << "]" ;
      cout << "\n";
    }
    cout << "\n" << setfill('-') << setw(64) << " " << setfill(' ');
    cout << "\n";
  }
  cout << "\n";
}

// Pre-condition: called by roomController() to move along the map
// Post-condition: returns true if the room has already been explored. Updates mapArray[] with current and previous player position. Updates roomExplored[] with true once a new room is entered
bool Map::move()
{
   // Prints the map
  mapPrint();

  // Set previousPlayerPosition to player position, to record the last movement
  previousPlayerPosition = &mapArray[rowPosition][columnPosition];

  // Place new value in previousPlayerPosition
  if (!(roomContents[rowPosition][columnPosition] == "Merchant" || roomContents[rowPosition][columnPosition] == "Exit"))
    *previousPlayerPosition = 'o'; // Place a 'o' value in previousPlayerPosition pointer's element to indicate a previously cleared room
  else if (roomContents[rowPosition][columnPosition] == "Merchant")
    *previousPlayerPosition = '$'; // Place a '$' value in previousPlayerPosition pointer's element to indicate a discovered merchant shop
  else if (roomContents[rowPosition][columnPosition] == "Exit")
    *previousPlayerPosition = '#'; // Place a '#' value in previousPlayerPosition pointer's element to indicate the exit

  // Adjusts either rowPosition or columnPosition by 1 or -1 based on direction choice by the user
  mapMovement();

  // Check if we've been in this room before
  bool roomCleared = false;
  if (roomExplored[rowPosition][columnPosition])
    roomCleared = true;
  else
    // Set the current index to true, since we'll be clearing this room next
    roomExplored[rowPosition][columnPosition] = true;

  // Place new value in player's current position
  mapArray[rowPosition][columnPosition] = '*';

  // Prints the map
  mapPrint();

  // Print map divider
  cout << setfill('-') << setw(64) << " " << setfill(' ') << "\n\n";

  // If the room was already visited, return true, if not, return false
  if (roomCleared)
    return true;
  else
    return false;
}

// Pre-condition: called by Map::move()
// Post-condition: updates row and column variables based on user selection
void Map::mapMovement()
{
  bool loopFlag = true;
  char directionChoice = ' ';
  do
  {
    // Accept direction from user, validates that the direction is within map bounds
    cout << "Which direction would you like to go? (N|E|S|W): ";
    cin >> directionChoice;
    cout << "\n";
    if (validateDirection(rowPosition, columnPosition, directionChoice, MAP_ROWS, MAP_COLUMNS))
      loopFlag = false;
  } while (loopFlag);

  // Adjust row and column values based on user choice
  switch (directionChoice)
  {
    case 'N':
    {
      --rowPosition;
      break;
    }
    case 'S':
    {
      ++rowPosition;
      break;
    }
    case 'E':
    {
      ++columnPosition;
      break;
    }
    case 'W':
    {
      --columnPosition;
      break;
    }
  }
}

// Pre-condition: called in the map constructor to generate a random map
// Post-condition: Performs calculations to decide where and how many of each room to spawn when calling generateRooms(). The spawn room is marked with an '*' in mapArray[] and 'true' in roomExplored[]. If debug is on - mapArray[] is additionally filled with room contents indicators
void Map::generateMap()
{
  // Place the player icon in the starter room and sets the starter room to "explored" with "start" contents
  mapArray[ROW_MIDPOINT][COLUMN_MIDPOINT] = '*';
  roomExplored[ROW_MIDPOINT][COLUMN_MIDPOINT] = true;
  roomContents[ROW_MIDPOINT][COLUMN_MIDPOINT] = "Start";

  // Spawn an exit on the map
  const int MIN_EXIT_DISTANCE = 3; // The exit must spawn 3 tiles away from the center
  bool validExitSpawns[MAP_ROWS][MAP_COLUMNS] = {0}; // This array finds a valid spawn location based on distance from spawn
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      if ((i <= ROW_MIDPOINT - MIN_EXIT_DISTANCE || i >= ROW_MIDPOINT + MIN_EXIT_DISTANCE) || (j <= COLUMN_MIDPOINT - MIN_EXIT_DISTANCE || j >= COLUMN_MIDPOINT + MIN_EXIT_DISTANCE))
        validExitSpawns[i][j] = true;
    }
  }
  bool exitPlaced = false;
  do
  {
    int randomRow = rand() % MAP_ROWS;
    int randomColumn = rand() % MAP_COLUMNS;
    if (validExitSpawns[randomRow][randomColumn])
    {
      mapArray[randomRow][randomColumn] = '#';
      roomContents[randomRow][randomColumn] = "Exit";
      exitPlaced = true;
    }
  } while (!exitPlaced);

  // Spawn Merchants
  const int MERCHANT_ROOMS_DISTANCE = 2; // Merchants must spawn 2 tiles away from the center
  const int MERCHANT_ROOMS_SIMILAR_DISTANCE = 1; // Merchants rooms must spawn 1 tile away from each other
  const int MERCHANT_ROOMS_ALLOWED = MAP_ROWS / 2 + 1; // Number of merchants to spawn is based on map size
  const string MERCHANT_ROOMS_NAME = "Merchant";
  const char MERCHANT_SYMBOL = '$';
  generateRooms(MERCHANT_ROOMS_NAME, MERCHANT_SYMBOL, MERCHANT_ROOMS_DISTANCE, MERCHANT_ROOMS_SIMILAR_DISTANCE, MERCHANT_ROOMS_ALLOWED);

  // Calculate Remaining Non-Enemy Rooms
  int REMAINING_ROOMS_DISTANCE = 2; // Non-enemy rooms must spawn 2 tiles away from the center, this is so the first room is guaranteed to contain an enemy
  int REMAINING_ROOMS_SIMILAR_DISTANCE = 1; // Non-enemy rooms must spawn 1 tiles away from each other
  int REMAINING_ROOMS_ALLOWED = (MAP_ROWS * MAP_COLUMNS) - 2 - MERCHANT_ROOMS_ALLOWED; // The literal 2 is for 1 exit and 1 spawn location

  // Spawn Loot Room
  const int LOOT_ROOMS_ALLOWED = REMAINING_ROOMS_ALLOWED * 0.15f; // 15% of remaining rooms can be loot rooms
  const string LOOT_ROOMS_NAME = "Loot";
  const char LOOT_ROOMS_SYMBOL = 'L';
  generateRooms(LOOT_ROOMS_NAME, LOOT_ROOMS_SYMBOL, REMAINING_ROOMS_DISTANCE, REMAINING_ROOMS_SIMILAR_DISTANCE, LOOT_ROOMS_ALLOWED);

  // Spawn Enemy Rooms
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      if (roomContents[i][j] == " ")
      {
        roomContents[i][j] = "Enemy";
        if (debug)
          mapArray[i][j] = 'E';
      }
    }
  }
}

// Pre-condition: called by generateMap() to randomly generate a selected room(s) for roomContets[]
// Post-condition: roomContents[] is filled with a random selection of the passed in room. If debug is on - mapArray[] is additionally filled with room contents indicators
void Map::generateRooms(const string &ROOM_NAME, const char ROOM_SYMBOL, const int ROOM_DISTANCE, const int SIMILAR_DISTANCE, const int ROOMS_ALLOWED)
{
  bool validSpawns[MAP_COLUMNS][MAP_COLUMNS] = {0}; // This array finds valid spawn locations based on distance from spawn and other from other spawns in this function
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
      // Mark the room as valid if the room is empty and a valid distance away from spawn
      if (roomContents[i][j] == " " && (i <= ROW_MIDPOINT - ROOM_DISTANCE || i >= ROW_MIDPOINT + ROOM_DISTANCE) || (j <= COLUMN_MIDPOINT - ROOM_DISTANCE || j >= COLUMN_MIDPOINT + ROOM_DISTANCE))
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
    int randomRow = rand() % MAP_ROWS;
    int randomColumn = rand() % MAP_COLUMNS;

    // Check to make sure the room is valid and empty before spawning the room
    if (validSpawns[randomRow][randomColumn] && roomContents[randomRow][randomColumn] == " ")
    {
      // Place room
      roomContents[randomRow][randomColumn] = ROOM_NAME;
      validSpawns[randomRow][randomColumn] = false;
      ++roomsPlaced;

      // DEBUG Option - Print loot room icons on map
      if (debug)
        mapArray[randomRow][randomColumn] = ROOM_SYMBOL;

      // Mark spaces SIMILAR_DISTANCE tile(s) away as invalid spawns, so rooms don't spawn too close to each other - if branches check bounds so I don't assign an out of bounds value
      // TODO num merchants not always correct
      if (randomRow + SIMILAR_DISTANCE < MAP_ROWS)
      {
        validSpawns[randomRow + SIMILAR_DISTANCE][randomColumn] = false;
        if (randomColumn + SIMILAR_DISTANCE < MAP_COLUMNS)
          validSpawns[randomRow + SIMILAR_DISTANCE][randomColumn + SIMILAR_DISTANCE] = false;
        if (randomColumn - SIMILAR_DISTANCE >= 0)
          validSpawns[randomRow + SIMILAR_DISTANCE][randomColumn - SIMILAR_DISTANCE] = false;
      }

      if (randomRow - SIMILAR_DISTANCE >= 0)
      {
        validSpawns[randomRow - SIMILAR_DISTANCE][randomColumn] = false;
        if (randomColumn - SIMILAR_DISTANCE >= 0)
          validSpawns[randomRow - SIMILAR_DISTANCE][randomColumn - SIMILAR_DISTANCE] = false;
        if (randomColumn + SIMILAR_DISTANCE < MAP_COLUMNS)
          validSpawns[randomRow - SIMILAR_DISTANCE][randomColumn + SIMILAR_DISTANCE] = false;
      }

      if (randomColumn + SIMILAR_DISTANCE < MAP_COLUMNS)
        validSpawns[randomRow][randomColumn + SIMILAR_DISTANCE] = false;
      if (randomColumn - SIMILAR_DISTANCE >= 0)
        validSpawns[randomRow][randomColumn - SIMILAR_DISTANCE] = false;
    }

    // Fallback exit if the spawning luck is poor
    else
      ++spawnAttempts;
  } while (roomsPlaced < ROOMS_ALLOWED && spawnAttempts < allowedAttempts);
}