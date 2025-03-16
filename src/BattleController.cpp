#include "BattleController.h"

#include <iostream>
#include <string>

#include "BattleArt.h"

namespace
{
  enum Result
  {
    WIN,
    LOSE,
    RUN
  };
}

int battleController(Player *player, Enemy *enemy)
{
  // Battle loop - loops until either the enemy or the player hits 0 health
  while (enemy->getHealth() > 0 && player->getCharacter()->getHealth() > 0)
  {
    // Displays the battleMenu and the player's choice is stored in battleSelection
    int battleSelection = art::battle::menu(player, enemy);

    // Player chose a damaging move
    if (battleSelection == art::battle::MELEE || battleSelection == art::battle::MAGIC || battleSelection == art::battle::RANGED)
    {
      // Translate battle selection to attack skill indexes
      int skillType = battleSelection - 1;

      int playerAttack = player->attack(skillType, enemy->getName(),enemy->getVulnerability(skillType));
      if (playerAttack > 0)
      {
        std::string skillName = player->getCharacter()->getSkillName(skillType);
        enemy->receive(playerAttack); // Subtracts playerDamage from enemyHealth, playerDamage passes the value from battleMenu to select a skill type (melee, mage, ranged)
      }
    }  

    else if (battleSelection == art::battle::HEAL)
      player->heal();

    else if (battleSelection == art::battle::RUN)
    {
      // Player has a 50% chance to successfully run, Bards can always run
      if (player->getCharacter()->getClassName() == "Bard" || 1 + (rand() % 100) <= 50)
      {
        std::cout << "\tYou escaped successfully!\n\n";
        return RUN;
      }
      else
        std::cout << "\tYou failed to escape!\n\n";
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
        std::cout << "Player Defeated!\n\n";
        return LOSE;
      }
    }
  }

  // Checks if the player won the battle
  if (enemy->getHealth() <= 0)
  {
    std::cout << "Enemy defeated!\n\n";
    // Returning a 1 means the player won the battle
    return WIN;
  }

  // TODO: Implement clean fix for return in all control paths
  return -1;
}
