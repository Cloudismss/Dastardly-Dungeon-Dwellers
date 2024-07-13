#include "Map Generator.h"

// Pre-condition: receives mapArray[], roomExplored[], roomContents[], *playerPosition, *exploredPosition, *contentsPosition, and constants from startGame()
// Post-condition: initializes mapArray[] with blanks and roomExplored[] with false, roomContents[] is filled with a random selection of rooms. The spawn room is marked with an '*' in mapArray[] and 'true' in roomExplored[]. If debug is on - mapArray[] is filled with room contents indicators
void generateMap(char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition, const int ROW_MIDPOINT, const int COLUMN_MIDPOINT)
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

  // Place the player icon in the starter room and sets the starter room to explored with "start" contents
  *playerPosition = '*';
  *exploredPosition = true;
  *contentsPosition = "Start";

  // Spawn an exit on the map
  const int MIN_EXIT_DISTANCE = 3; // The exit must spawn 3 tiles away from the center
  bool validExitSpawns[MAP_ROWS][MAP_COLUMNS] = {0}; // This array finds a valid spawn location based on distance from spawn
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      if ((i <= ROW_MIDPOINT - MIN_EXIT_DISTANCE || i >= ROW_MIDPOINT + MIN_EXIT_DISTANCE) || (j <= COLUMN_MIDPOINT - MIN_EXIT_DISTANCE || j >= COLUMN_MIDPOINT + MIN_EXIT_DISTANCE))
      {
        validExitSpawns[i][j] = true;
      }
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
  int merchantDistance = 2; // Merchants must spawn 2 tiles away from the center
  int merchantSimilarDistance = 1; // Merchants rooms must spawn 1 tile away from each other
  int merchantsAllowed = MAP_ROWS / 2 + 1; // Number of merchants to spawn is based on map size
  string merchantName = "Merchant";
  char merchantSymbol = '$';
  generateMapRoomSpawner(ROW_MIDPOINT, COLUMN_MIDPOINT, merchantDistance, merchantSimilarDistance, merchantsAllowed, merchantName, merchantSymbol, mapArray, roomContents);

  // Spawn Remaining Non-Enemy Rooms
  int remainingRoomsDistance = 2; // Non-enemy rooms must spawn 2 tiles away from the center, this is so the first room is guaranteed to contain an enemy
  int remainingRoomsSimilarDistance = 1; // Non-enemy rooms must spawn 1 tiles away from each other
  int remainingRoomsAvailable = (MAP_ROWS * MAP_COLUMNS) - 2 - merchantsAllowed; // The literal 2 is for 1 exit and 1 spawn location

  // Spawn Loot Room
  int lootRoomsAllowed = remainingRoomsAvailable * 0.15f; // 15% of remaining rooms can be loot rooms
  string lootRoomName = "Loot";
  char lootRoomSymbol = 'L';
  generateMapRoomSpawner(ROW_MIDPOINT, COLUMN_MIDPOINT, remainingRoomsDistance, remainingRoomsSimilarDistance, lootRoomsAllowed, lootRoomName, lootRoomSymbol, mapArray, roomContents);

  // Spawn Enemy Rooms
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      if (roomContents[i][j] == " ")
      {
        roomContents[i][j] = "Enemy";
        if (debug)
        {
          mapArray[i][j] = 'E';
        }
      }
    }
  }
}

// Pre-condition: receives mapArray[], roomContents[], and constants from generateMap()
// Post-condition: roomContents[] is filled with a random selection of rooms. If debug is on - mapArray[] is filled with room contents indicators
void generateMapRoomSpawner(const int ROW_MIDPOINT, const int COLUMN_MIDPOINT, const int ROOM_DISTANCE, const int SIMILAR_DISTANCE, const int ROOMS_ALLOWED, const string &roomName, char roomSymbol, char mapArray[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS])
{
  bool validSpawns[MAP_COLUMNS][MAP_COLUMNS] = {0}; // This array finds valid spawn locations based on distance from spawn and other from other spawns in this function
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      // Mark the room as valid if the room is empty and a valid distance away from spawn
      if (roomContents[i][j] == " " && (i <= ROW_MIDPOINT - ROOM_DISTANCE || i >= ROW_MIDPOINT + ROOM_DISTANCE) || (j <= COLUMN_MIDPOINT - ROOM_DISTANCE || j >= COLUMN_MIDPOINT + ROOM_DISTANCE))
      {
        validSpawns[i][j] = true;
      }
    }
  }

  // Using these variable to make sure the function has a way out if it can't find a spawn after x attempts
  int spawnAttempts = 0;
  int allowedAttempts = 10;
  if (roomName == "Merchant")
  {
    allowedAttempts = 100; // I want to ensure the proper amount of merchants are always spawned
  }

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
      roomContents[randomRow][randomColumn] = roomName;
      validSpawns[randomRow][randomColumn] = false;
      ++roomsPlaced;

      // DEBUG Option - Print loot room icons on map
      if (debug)
      {
        mapArray[randomRow][randomColumn] = roomSymbol;
      }

      // Mark spaces SIMILAR_DISTANCE tile(s) away as invalid spawns, so rooms don't spawn too close to each other - if branches check bounds so I don't assign an out of bounds value
      // TODO num merchants not always correct
      if (randomRow + SIMILAR_DISTANCE < MAP_ROWS)
      {
        validSpawns[randomRow + SIMILAR_DISTANCE][randomColumn] = false;
        if (randomColumn + SIMILAR_DISTANCE < MAP_COLUMNS)
        {
          validSpawns[randomRow + SIMILAR_DISTANCE][randomColumn + SIMILAR_DISTANCE] = false;
        }
        if (randomColumn - SIMILAR_DISTANCE >= 0)
        {
          validSpawns[randomRow + SIMILAR_DISTANCE][randomColumn - SIMILAR_DISTANCE] = false;
        }
      }

      if (randomRow - SIMILAR_DISTANCE >= 0)
      {
        validSpawns[randomRow - SIMILAR_DISTANCE][randomColumn] = false;
        if (randomColumn - SIMILAR_DISTANCE >= 0)
        {
          validSpawns[randomRow - SIMILAR_DISTANCE][randomColumn - SIMILAR_DISTANCE] = false;
        }
        if (randomColumn + SIMILAR_DISTANCE < MAP_COLUMNS)
        {
          validSpawns[randomRow - SIMILAR_DISTANCE][randomColumn + SIMILAR_DISTANCE] = false;
        }
      }

      if (randomColumn + SIMILAR_DISTANCE < MAP_COLUMNS)
      {
        validSpawns[randomRow][randomColumn + SIMILAR_DISTANCE] = false;
      }
      if (randomColumn - SIMILAR_DISTANCE >= 0)
      {
        validSpawns[randomRow][randomColumn - SIMILAR_DISTANCE] = false;
      }
    }

    // Fallback exit if the spawning luck is poor
    else
    {
      ++spawnAttempts;
    }
  } while (roomsPlaced < ROOMS_ALLOWED && spawnAttempts < allowedAttempts);
}