#include "Room Enemy.h"

// Pre-condition: called by roomController(), passed enemyProgression, inventory variables and className / characterStats
// Post-condition: Returns true if the player survives the room, updates inventory variables based on result
bool roomEnemy(string &className, int &potionCount, int armorCount, int &goldCount, int &keyCount, int enemyProgression, std::ifstream &characterStats)
{
  // Run the battleController function. It returns 1 if the player wins the battle, -1 if the player successfully runs away, and 0 if they lose.
  int rewardTier = 1;
  int battleResult = battleController(className, rewardTier, potionCount, armorCount, enemyProgression, characterStats);

  // Control variable that enables the pause screen after winning the battle
  bool battleSuccess = false;

  // Player won the battle
  if (battleResult == 1)
  {
    battleSuccess = true;

    cout << "You check the enemy for valuables:\n";
    int lootRoll = 1 + (rand() % 100);

    if (rewardTier == 1)
    {
      // 10% chance to earn a potion
      if (lootRoll <= 10)
      {
        ++potionCount;
        cout << "Potion added\n";
      }

      // 85% chance to earn a random amount of gold
      if (lootRoll <= 85)
      {
        // Amount of gold returned is between 5-15
        int goldAdded = 5 + (rand() % 11);
        goldCount += goldAdded;
        cout << "Gold x" << goldAdded << " added\n";
      }

      // Nothing found
      if (lootRoll > 85)
      {
        cout << "You found nothing of value\n";
      }
    }

    else if (rewardTier == 2)
    {
      // 30% chance to earn a potion
      if (lootRoll <= 30)
      {
        ++potionCount;
        cout << "Potion added\n";
      }

      // 90% chance to earn a random amount of gold
      if (lootRoll <= 90)
      {
        // Amount of gold returned is between 5-20
        int goldAdded = 5 + (rand() % 16);
        goldCount += goldAdded;
        cout << "Gold x" << goldAdded << " added\n";
      }

      // Nothing found
      if (lootRoll > 90)
      {
        cout << "You found nothing of value\n";
      }
    }

    else if (rewardTier == 3)
    {
      // 60% chance to earn a potion(s)
      if (lootRoll <= 60)
      {
        int potionAdded = 1 + (rand() % 2);
        potionCount += potionAdded;
        if (potionAdded == 1)
        {
          cout << "Potion added\n";
        }
        else
        {
          cout << "Potion x" << potionAdded << " added\n";
        }
      }

      // 100% chance to earn a random amount of gold between 10-20
      int goldAdded = 10 + (rand() % 11);
      goldCount += goldAdded;
      cout << "Gold x" << goldAdded << " added\n";
    }

    else if (rewardTier == 4)
    {
      // 90% chance to earn a potion(s)
      if (lootRoll <= 90)
      {
        int potionAdded = 1 + (rand() % 2);
        potionCount += potionAdded;
        if (potionAdded == 1)
        {
          cout << "Potion added\n";
        }
        else
        {
          cout << "Potion x" << potionAdded << " added\n";
        }
      }

      // 100% chance to earn a random amount of gold between 15-20
      int goldAdded = 15 + (rand() % 6);
      goldCount += goldAdded;
      cout << "Gold x" << goldAdded << " added\n";

      // 5% chance to earn the golden key
      if (lootRoll <= 5)
      {
        ++keyCount;
        cout << "\n";
        displayMeInABox("GOLDEN KEY Acquired!");
      }
    }

    else if (rewardTier == 5)
    {
      // 100% chance to earn a potion(s)
      int potionAdded = 1 + (rand() % 2);
      potionCount += potionAdded;
      cout << "Potion x" << potionAdded << " added\n";

      // 100% chance to earn a random amount of gold between 15-20
      int goldAdded = 15 + (rand() % 6);
      goldCount += goldAdded;
      cout << "Gold x" << goldAdded << " added\n";

      // 15% chance to earn the golden key
      if (lootRoll <= 15)
      {
        ++keyCount;
        cout << "\n";
        displayMeInABox("GOLDEN KEY Acquired!");
      }
    }

    else if (rewardTier == 10)
    {
      // 100% chance to earn 5-10 potions
      int potionAdded = 5 + (rand() % 6);
      potionCount += potionAdded;
      cout << "Potion x" << potionAdded << " added\n";

      // 100% chance to earn a random amount of gold between 25-50
      int goldAdded = 25 + (rand() % 26);
      goldCount += goldAdded;
      cout << "Gold x" << goldAdded << " added\n";

      // 100% chance to earn the golden key
      ++keyCount;
      cout << "\n";
      displayMeInABox("GOLDEN KEY Acquired!");
    }
    cout << "\n";
  }

  // Player successfully ran away
  else if (battleResult == -1)
  {
    battleSuccess = true;
  }

  // This check ensures the player isn't asked for the next room after they lose
  if (battleSuccess)
  {
    // Pause the game until the user is ready
    cout << "Press enter to continue to the next room: ";
    string enterKey = " ";
    getline(cin, enterKey);
    cout << "\n";
  }

  // If battleSuccess is false, end the program
  return battleSuccess;
}