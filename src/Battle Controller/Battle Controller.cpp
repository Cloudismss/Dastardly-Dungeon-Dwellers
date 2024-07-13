#include "Battle Controller.h"

// Pre-condition: called by battleController(), passed skill and health variables
// Post-condition: returns user selection from displayed battleMenu
int battleMenu(string &meleeName, string &magicName, string &rangedName, int playerHealth, int enemyHealth)
{
  // Menu Variables
  int boxWidth = 63;
  int borderSpacing = ((boxWidth - 23) / 2);
  string choiceName[] = {meleeName, magicName, rangedName};

  short int battleMenuSelection = 0;
  bool loopFlag = true;
  do
  {
    battleHealthArt(playerHealth, enemyHealth);
    cout << "." << setfill('-') << setw(boxWidth) << ".\n"
         << "|" << setfill(' ') << setw(boxWidth) << "|\n"
         << "|" << setw(12) << " " << "1. " << choiceName[0] << setw(borderSpacing - choiceName[0].length()) << " " << "4. Heal" << setw(18) << " " << " |\n"
         << "|" << setw(12) << " " << "2. " << choiceName[1] << setw( borderSpacing - choiceName[1].length()) << " " << "5. Run Away" << setw(14) << " " << " |\n"
         << "|" << setw(12) << " " << "3. " << choiceName[2] << setw(borderSpacing - choiceName[2].length()) << " " << "6. Help" << setw(18) << " " << " |\n"
         << "|" << setfill(' ') << setw(boxWidth) << "|\n"
         << "'" << setfill('-') << setw(boxWidth) << "'\n"
         << setfill(' ') << "\n"
         << "\tMake a selection: ";
    battleMenuSelection = 0;
    cin >> battleMenuSelection;
    if (validateInput(battleMenuSelection, 1, 6))
    {
      if (battleMenuSelection != 6)
      {
        loopFlag = false;
      }
      else
      {
        cout << "\n";
        tutorialBattle();
      }
    }
  } while (loopFlag);
  cout << "\n";
  return battleMenuSelection;
}

// Pre-condition: called by roomEnemy(), passed inventory variables, enemyProgression, rewardTier and className / characterStats
// Post-condition: returns 1 if the player won the battle, -1 if the player ran away, 0 if they lost, updates inventory variables, playerHealth, and updates rewardTier based on battleEnemySpawner()
int battleController(const string &className, int &rewardTier, int &potionCount, int armorCount, int enemyProgression, std::ifstream &characterStats)
{
  // Player health variable
  static int playerHealth = 20;

  if (debug)
  {
    playerHealth = 100;
  }

  // Fills skill names with default names based on class selection
  static string meleeName = " ", magicName = " ", rangedName = " ";
  static bool initializeNames = false;
  if (!initializeNames)
  {
    string upgradeMessage = " ";
    skillNames(meleeName, "Melee", upgradeMessage, className);
    skillNames(magicName, "Magic", upgradeMessage, className);
    skillNames(rangedName, "Ranged", upgradeMessage, className);
    initializeNames = true;
  }

  // Enemy Spawner
  int enemyTier = 0, enemyHealth = 0;
  string enemyName = " ";
  bool boss = false;
  battleEnemySpawner(enemyTier, rewardTier, enemyHealth, enemyName, enemyProgression, boss);

  // Battle loop - loops until either the enemy or the player hits 0 health
  while (enemyHealth > 0 && playerHealth > 0)
  {
    // Displays the battleMenu and the player's choice is stored in battleMenuSelection
    int battleMenuSelection = battleMenu(meleeName, magicName, rangedName, playerHealth, enemyHealth);

    // Player chose a damaging move
    if (battleMenuSelection >= 1 && battleMenuSelection <= 3)
    {
      // Subtracts playerDamage from enemyHealth, playerDamage passes the value from battleMenu to select a skill type (melee, mage, ranged)
      enemyHealth -= playerDamage(battleMenuSelection, meleeName, magicName, rangedName, className, enemyName, boss, characterStats);

      // The enemy is permitted to attack only if their health is > 0, this prevents the enemy from attacking after their health reaches 0
      if (enemyHealth > 0)
      {
        // Enemy damage is based on the (enemy tier * base enemy damage) + a random number between 1 and 3
        playerHealth -= enemyDamage(enemyTier, enemyName, boss, armorCount);
      }
    }

    // Player chose to heal
    else if (battleMenuSelection == 4)
    {
      // A random heal amount is added to playerHealth
      playerHealth += heal(potionCount);

      // Enemy damage is based on the (enemy tier * base enemy damage) + a random number between 1 and 3
      playerHealth -= enemyDamage(enemyTier, enemyName, boss, armorCount);
    }

    // Player chose to run
    else if (battleMenuSelection == 5)
    {
      // Player has a 50% chance to successfully run, Bards can always run
      if (className == "Bard" || 1 + (rand() % 100) <= 50)
      {
        cout << "\tYou escaped successfully!\n\n";
        // Returning a -1 means successful escape
        return -1;
      }

      // Player failed to run
      else
      {
        cout << "\tYou failed to escape!\n\n";
        // Enemy damage is based on the (enemy tier * base enemy damage) + a random number between 1 and 3
        playerHealth -= enemyDamage(enemyTier, enemyName, boss, armorCount);
      }
    }
  }

  // Checks if the player won the battle
  if (enemyHealth <= 0)
  {
    cout << "Enemy defeated!\n\n";
    // Returning a 1 means the player won the battle
    return 1;
  }

  // Checks if the player lost the battle
  if (playerHealth <= 0)
  {
    cout << "Player Defeated!\n\n";
    // Returning a 0 means the player lost the battle
    return 0;
  }
}