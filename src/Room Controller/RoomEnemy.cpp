#include "RoomEnemy.h"

#include <iostream>
#include <string>

#include "BattleController.h"
#include "EnemySpawner.h"
#include "Loot.h"

using std::cin;
using std::cout;
using std::string;

bool roomEnemy(Player *player)
{
  Enemy *enemy = EnemySpawner::generateEnemy(player->getCharacter()->getLevel());

  // Run the battleController function. It returns 1 if the player wins the battle, -1 if the player successfully runs away, and 0 if they lose.
  int battleResult = battleController(player, enemy);

  // Player lost the battle - end the program
  if (battleResult == LOSE)
    return false;

  // Player won the battle - collect loot
  if (battleResult == WIN)
    loot(player, enemy);

  delete enemy;

  // Pause the game until the user is ready
  cout << "Press enter to continue to the next room: ";
  string enterKey = " ";
  getline(cin, enterKey);
  cout << "\n";

  // Continue the game
  return true;
}
