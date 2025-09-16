#include "BattleArt.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "Globals.h"

#include "TutorialArt.h"

#include "Enemy.h"
#include "Player.h"
#include "Validation.h"

namespace art::battle
{
int menu(Player *player, Enemy *enemy)
{
  // Menu Variables
  int boxWidth = 63;
  int borderSpacing = ((boxWidth - 23) / 2);
  std::string choiceName[] = { player->getCharacter()->getSkillName(skill::MELEE),
                               player->getCharacter()->getSkillName(skill::MAGIC),
                               player->getCharacter()->getSkillName(skill::RANGED) };
  std::string potionElement = "Potions: " + std::to_string(player->getPotions());

  int battleSelection;
  bool loopFlag = true;
  do
  {
    displayHealth(player->getCharacter()->getClassName(), player->getCharacter()->getHealth(), enemy->getNickname(),
                  enemy->getHealth());
    std::cout << "." << std::setfill('-') << std::setw(boxWidth) << ".\n"
              << "|" << std::setfill(' ') << std::setw(boxWidth) << "|\n"
              << "|" << std::setw(12) << " " << "1: " << choiceName[0] << std::setw(borderSpacing - choiceName[0].length()) << " "
              << "4: Heal" << std::setw(18) << " " << " |\n"
              << "|" << std::setw(12) << " " << "2: " << choiceName[1] << std::setw(borderSpacing - choiceName[1].length()) << " "
              << "5: Run Away" << std::setw(14) << " " << " |\n"
              << "|" << std::setw(12) << " " << "3: " << choiceName[2] << std::setw(borderSpacing - choiceName[2].length()) << " "
              << "6: Switch Character" << std::setw(18 - 12) << " " << " |\n"
              << "|" << std::setfill(' ') << std::setw(boxWidth) << "|\n"
              << "|" << " " << potionElement << std::setfill(' ') << std::setw(boxWidth - potionElement.size() - 1) << "0: Help |\n"
              << "'" << std::setfill('-') << std::setw(boxWidth) << "'\n"
              << std::setfill(' ') << "\n"
              << "\tMake a selection: ";
    std::cin >> battleSelection;
    if (validate::input(battleSelection, 0, 6))
    {
      if (battleSelection == HELP)
      {
        std::cout << "\n";
        art::tutorial::tutorialBattle();
      }
      else if (battleSelection < SWITCH)
        loopFlag = false;
      else if (battleSelection == SWITCH)
      {
        if (!player->cycle())
          std::cout << "\n\tI cannot abandon this fight...\n\n";
        else
          loopFlag = false;
      }
    }
  } while (loopFlag);
  std::cout << "\n";

  return battleSelection;
}

void displayHealth(const std::string &className, int playerHealth, const std::string &enemyName, int enemyHealth)
{
  // Don't print health if either the player or the enemy has 0 health
  if (playerHealth <= 0 || enemyHealth <= 0)
    return;

  // Print health
  else
  {
    std::string playerHealthDisplay = className + " health: ";
    playerHealthDisplay += std::to_string(playerHealth);
    std::string enemyHealthDisplay = enemyName + " health: ";
    enemyHealthDisplay += std::to_string(enemyHealth);

    int boxWidth = 63;
    int midpoint = boxWidth / 2;
    int leftGap = 5, rightGap = 6;
    int gapSize = ((midpoint - playerHealthDisplay.length()) + (midpoint - enemyHealthDisplay.length()) - (leftGap + rightGap));

    std::cout << "." << std::setfill('-') << std::setw(leftGap + playerHealthDisplay.length()) << "." << std::setfill(' ')
              << std::setw(gapSize) << " " << "." << std::setfill('-') << std::setw(rightGap + enemyHealthDisplay.length()) << ".\n"
              << "|" << std::setfill(' ') << std::setw(2) << " " << playerHealthDisplay << std::setw(2) << " " << "|"
              << std::setw(gapSize) << " " << "|" << std::setw(2) << " " << enemyHealthDisplay << std::setw(4) << "|\n"
              << "'" << std::setfill('-') << std::setw(leftGap + playerHealthDisplay.length()) << "'" << std::setfill(' ')
              << std::setw(gapSize) << " " << "'" << std::setfill('-') << std::setw(rightGap + enemyHealthDisplay.length()) << "'\n"
              << std::setfill(' ');
  }
}
} // namespace art::battle
