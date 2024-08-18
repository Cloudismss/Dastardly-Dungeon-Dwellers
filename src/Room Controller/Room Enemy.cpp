#include "Room Enemy.h"

#include <iostream>
#include <string>

#include "Battle Controller.h"
#include "Loot.h"

using std::cin;
using std::cout;
using std::string;

// Pre-condition: called by roomController(), passed enemyProgression, inventory variables and className / characterStats
// Post-condition: Returns true if the player survives the room, updates inventory variables based on result
bool roomEnemy(Player *player)
{
  // Generate enemy
  Enemy *enemy = new Enemy(player->getProgression());

  // Run the battleController function. It returns 1 if the player wins the battle, -1 if the player successfully runs away, and 0 if they lose.
  int battleResult = battleController(player, enemy);

  // Player lost the battle - end the program
  if (battleResult == 0)
    return false;

  // Player won the battle
  if (battleResult == 1)
    loot(player, enemy);

  delete enemy;

  // Pause the game until the user is ready
  cout << "Press enter to continue to the next room: ";
  string enterKey = " ";
  getline(cin, enterKey);
  cout << "\n";

  // Continue the game since the player won the battle
  return true;
}