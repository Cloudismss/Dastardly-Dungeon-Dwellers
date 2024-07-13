#include "Map.h"

// Pre-condition: called by roomController(), passed mapArray[], roomExplored[], roomContents[], array pointers
// Post-condition: Returns true if the room has already been explored. Allows the player to move around the map. Updates mapArray[] with current and previous player position. Updates roomExplored[] with true once a new room is entered
bool map(char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition)
{
  // Position Tracking Variables
  static int rowPosition = MAP_ROWS / 2, columnPosition = MAP_COLUMNS / 2;
  static char *previousPlayerPosition = &mapArray[MAP_ROWS / 2][MAP_COLUMNS / 2];

  // Prints the map
  cout << setfill('-') << setw(64) << " " << setfill(' ');
  cout << "\n\n";
  cout << "MAP SELECTION" << "\n\n";
  cout << "You are here [*]\n";
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      cout << "[" << mapArray[i][j] << "]" ;
    }
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
      {
        cout << "[" << roomExplored[i][j] << "]" ;
      }
      cout << "\n";
    }
    cout << "\n";
    for (int i = 0; i < MAP_ROWS; ++i)
    {
      for (int j = 0; j < MAP_COLUMNS; ++j)
      {
        cout << "[" << roomContents[i][j] << "]" ;
      }
      cout << "\n";
    }
    cout << "\n" << setfill('-') << setw(64) << " " << setfill(' ');
    cout << "\n";
  }
  cout << "\n";

  // Adjusts either rowPosition or columnPosition by 1 or -1 based on direction choice by the user
  mapMovement(rowPosition, columnPosition);

  // Move the pointers to new positions based on direction choice by the user
  playerPosition = &mapArray[rowPosition][columnPosition];
  exploredPosition = &roomExplored[rowPosition][columnPosition];

  // Check if we've been in this room before
  bool roomCleared = false;
  if (*exploredPosition)
  {
    roomCleared = true;
  }
  else
  {
    // Set the current index to true, since we'll be clearing this room next
    *exploredPosition = true;
  }

  // Place new value in previousPlayerPosition
  if (!(*contentsPosition == "Merchant" || *contentsPosition == "Exit"))
  {
    *previousPlayerPosition = 'o'; // Place a 'o' value in previousPlayerPosition pointer's element to indicate a previously cleared room
  }
  else if (*contentsPosition == "Merchant")
  {
    *previousPlayerPosition = '$'; // Place a '$' value in previousPlayerPosition pointer's element to indicate a discovered merchant shop
  }
  else if (*contentsPosition == "Exit")
  {
    *previousPlayerPosition = '#'; // Place a '#' value in previousPlayerPosition pointer's element to indicate the exit
  }

  // Moving this pointer last out of the bunch, so previousPlayerPosition can read its value before contentsPosition moves
  contentsPosition = &roomContents[rowPosition][columnPosition];

  // Place new value in playerPosition
  *playerPosition = '*'; // Place an asterisk value in playerPosition pointer's element

  // Set previousPlayerPosition to playerPosition, to record the last movement
  previousPlayerPosition = playerPosition;

  // Prints the map
  cout << "You are here [*]\n";
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      cout << "[" << mapArray[i][j] << "]" ;
    }
    cout << "\n";
  }
  cout << "\n";
  cout << setfill('-') << setw(64) << " " << setfill(' ') << "\n\n";

  // If the room was already visited, return true, if not, return false
  if (roomCleared)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Pre-condition: called by map(), passed rowPosition and columnPosition
// Post-condition: updates both variables based on user selection
void mapMovement(int &rowPosition, int &columnPosition)
{
  bool loopFlag = true;
  char directionChoice = ' ';
  do
  {
    // Accept direction from user, validates that the direction is within map bounds
    cout << "Which direction would you like to go? (N|E|S|W): ";
    cin >> directionChoice;
    cout << "\n";
    if (validateDirection(rowPosition, columnPosition, directionChoice))
    {
      loopFlag = false;
    }
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