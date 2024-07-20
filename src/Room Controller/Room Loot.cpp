#include "Room Loot.h"

// Pre-condition: called by roomController(), passed enemyProgression, isEnemyRoom, inventory variables and className / characterStats
// Post-condition: Returns true if the player survives the room, updates inventory variables based on result, isEnemyRoom is updated to true if an enemy is spawned
bool roomLoot(Player *player, bool &isEnemyRoom)
{
  // This room could be a trap, ask the player if they want to attempt to loot the chest
  bool lootSuccess = false;
  bool loopFlag = true;
  char chestSelection = ' ';
  do
  {
    cout << "Do you look inside?\n"
         << "Y or N:";
    cin >> chestSelection;
    if (validateDecision(chestSelection))
    {
      loopFlag = false;
    }
  } while (loopFlag);

  // Player wants to open the chest
  if (chestSelection == 'Y' || chestSelection == 'y')
  {
    cout << "\nYou carefully lift the lid open";

    // There is a 90% chance the room isn't a trap
    if (1 + (rand() % 100) <= 90)
    {
      cout << " and found the following items:\n";

      // Player is guaranteed a random amount of gold between 15-30
      int goldAdded = 15 + (rand() % 16);
      player->addGold(goldAdded);
      cout << "Gold x" << goldAdded << " added\n";

      int lootRoll = 1 + (rand() % 100);

      // 75% chance the player is given potion(s)
      if (lootRoll <= 75)
      {
        // Player is given a random amount of potions between 2-3
        int potionAdded = 2 + (rand() % 2);
        player->addPotion(potionAdded);
        if (potionAdded > 1)
        {
          cout << "Potion x" << potionAdded << " added\n";
        }
        else
        {
          cout << "Potion added\n";
        }
      }
      cout << "\n";

      // 30% chance the player is given the golden key
      if (lootRoll <= 30)
      {
        player->addKey();
        displayMeInABox("GOLDEN KEY Acquired!");
      }

      // Player successfully cleared the room
      lootSuccess = true;

      // Pause the game until the user is ready
      cout << "Press enter to continue to the next room: ";
      string enterKey = " ";
      getline(cin, enterKey);
      cout << "\n";
    }

    // There is a 10% chance the room is a trap
    else
    {
      cout << " but it's empty!\n"
           << "You quickly slam the lid closed as you hear the door in front of you crack open!\n\n";

      // Run roomEnemy, Returns true if the player wins the battle
      if (roomEnemy(player))
      {
        lootSuccess = true;
        isEnemyRoom = true;
      }
    }
  }

  // Player chose not to open the chest
  else
  {
    cout << "\nYou sense this may be a trap, and quickly exit the room\n\n";
    lootSuccess = true;

    // Pause the game until the user is ready
    cout << "Press enter to continue to the next room: ";
    string enterKey = " ";
    getline(cin, enterKey);
    cout << "\n";
  }

  // If a battle is triggered and lost, a false value will end the program
  return lootSuccess;
}