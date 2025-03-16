#include "RoomExit.h"

#include <iostream>

#include "Game.h"
#include "Validation.h"

using std::cin;
using std::cout;

void roomExit(Player *player)
{
  // Check if the player has the golden key
  if (player->getKeys() > 0)
  {
    bool loopFlag = true;
    char selection = ' ';
    do
    {
      cout << "Would you like use your golden key to exit the dungeon?\n"
           << "Y or N:";
      cin >> selection;
      if (validate::decision(selection))
        loopFlag = false;
    } while (loopFlag);

    // Player chose to leave the dungeon, victory!
    if (selection == 'Y' || selection == 'y')
    {
      cout << "\n";
      Game::winCondition = true;
      return;
    }
  }

  // Player doesn't have a golden key
  else
    cout << "You don't have a golden key!\n\n";
}
