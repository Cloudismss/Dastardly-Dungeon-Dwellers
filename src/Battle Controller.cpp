#include "Battle Controller.h"

#include <iostream>
#include <string>

#include "Art.h"

using std::cout;
using std::string;

// Pre-condition: called by roomEnemy(), passed player and enemy objects
// Post-condition: returns 1 if the player won the battle, -1 if the player ran away, 0 if they lost, updates player variables
int battleController(Player *player, Enemy *enemy)
{
  // Battle loop - loops until either the enemy or the player hits 0 health
  while (enemy->getHealth() > 0 && player->getCharacter()->getHealth() > 0)
  {
    // Displays the battleMenu and the player's choice is stored in battleMenuSelection
    const string battleMenuSelection = art::battle::battleMenu(player, enemy);

    // Player chose a damaging move
    if (battleMenuSelection == "Melee" || battleMenuSelection == "Magic" || battleMenuSelection == "Ranged")
    {
      short unsigned int playerAttack = player->attack(battleMenuSelection, enemy->getName(),enemy->getVulnerability(battleMenuSelection));
      if (playerAttack > 0)
      {
        string skillName = player->getCharacter()->getSkillName(battleMenuSelection);
        enemy->receive(playerAttack); // Subtracts playerDamage from enemyHealth, playerDamage passes the value from battleMenu to select a skill type (melee, mage, ranged)
      }
    }  
    // Player chose to heal
    else if (battleMenuSelection == "Heal")
      player->heal(); // A random heal amount is added to playerHealth
    // Player chose to run
    else if (battleMenuSelection == "Run")
    {
      // Player has a 50% chance to successfully run, Bards can always run
      if (player->getCharacter()->getClassName() == "Bard" || 1 + (rand() % 100) <= 50)
      {
        cout << "\tYou escaped successfully!\n\n";
        return -1; // Returning a -1 indicates a successful escape
      }
      // Player failed to run
      else
        cout << "\tYou failed to escape!\n\n";
    }

    // The enemy is permitted to attack only if their health is > 0, this prevents the enemy from attacking after their health reaches 0
    // Enemy damage is based on the (enemy level * base enemy damage) + a random number between 1 and 3
    if (enemy->getHealth() > 0)
      player->getCharacter()->adjustHealth(-1 * enemy->attack(player->getArmor(), player->getCharacter()->getMaxHealth()));

    if (player->getCharacter()->getHealth() <= 0)
    {
      // Checks if the player has another character to switch to
      if (!player->getCharacter()->removeCurrentCharacter())
      {
        // Player is out of characters - game over
        cout << "Player Defeated!\n\n";
        return 0;
      }
    }
  }

  // Checks if the player won the battle
  if (enemy->getHealth() <= 0)
  {
    cout << "Enemy defeated!\n\n";
    // Returning a 1 means the player won the battle
    return 1;
  }

  // TODO: Implement clean fix for return in all control paths
  return -1;
}
