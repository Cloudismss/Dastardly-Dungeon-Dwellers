#include "Room Exit.h"

// Pre-condition: called by roomController(), passed keyCount and gameVictory
// Post-condition: updates gameVictory to true if the player chooses to leave the dungeon - game ends
void roomExit(int &keyCount, bool &gameVictory)
{
  // Check if the player has the golden key
  if (keyCount > 0)
  {
    bool loopFlag = true;
    char selection = ' ';
    do
    {
      cout << "Would you like use your golden key to exit the dungeon?\n"
           << "Y or N:";
      cin >> selection;
      if (validateDecision(selection))
      {
        loopFlag = false;
      }
    } while (loopFlag);

    // Player chose to leave the dungeon, victory!
    if (selection == 'Y' || selection == 'y')
    {
      cout << "\n";
      gameVictory = true;
      return;
    }
  }

  // Player doesn't have a golden key
  else
  {
    cout << "You don't have a golden key!\n\n";
  }
}