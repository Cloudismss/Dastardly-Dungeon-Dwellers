#include "RoomLoot.h"

#include <iostream>
#include <string>

#include "Player.h"
#include "Validation.h"

#include "RoomEnemy.h"

bool roomLoot(Player *player, bool &isEnemyRoom)
{
  // This room could be a trap, ask the player if they want to attempt to loot the chest
  bool lootSuccess = false;
  bool loopFlag = true;
  char chestSelection = ' ';
  do
  {
    std::cout << "Do you look inside?\n"
         << "Y or N:";
    std::cin >> chestSelection;
    if (validate::decision(chestSelection))
      loopFlag = false;
  } while (loopFlag);

  if (chestSelection == 'Y' || chestSelection == 'y')
  {
    std::cout << "\nYou carefully lift the lid open";

    // There is a 90% chance the room isn't a trap
    if (1 + (rand() % 100) <= 90)
    {
      std::cout << " and found the following items:\n";

      // Player is guaranteed a random amount of gold between 15-30
      player->addGold(15 + (rand() % 16));

      int lootRoll = 1 + (rand() % 100);

      // 75% chance the player is given potion(s) between 2-3
      if (lootRoll <= 75)
        player->addPotions(2 + (rand() % 2));

      std::cout << "\n";

      // 30% chance the player is given the golden key
      if (lootRoll <= 30)
        player->addKeys();

      // Player successfully cleared the room
      lootSuccess = true;

      // There is a 30% chance to find a new character
      if (1 + (rand() % 100) <= 30 && Character::available())
      {
        std::cout << "One of your fellow adventurers enters the room and compliments you on your prize...\n";
        bool loopFlag = true;
        char characterSelection;
        do
        {
          std::cout << "Do you invite them to join your party?\n"
              << "Y or N: ";
          std::cin >> characterSelection;
          if (validate::decision(characterSelection))
            loopFlag = false;
        } while (loopFlag);

        std::cout << "\n";

        if (characterSelection == 'Y' || characterSelection == 'y')
          player->appendRandomCharacter();

      }

      // Pause the game until the user is ready
      std::cout << "Press enter to continue to the next room: ";
      std::string enterKey;
      getline(std::cin, enterKey);
      std::cout << "\n";
    }

    // There is a 10% chance the room is a trap
    else
    {
      std::cout << " but it's empty!\n"
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
    std::cout << "\nYou sense this may be a trap, and quickly exit the room\n\n";
    lootSuccess = true;

    // Pause the game until the user is ready
    std::cout << "Press enter to continue to the next room: ";
    std::string enterKey;
    getline(std::cin, enterKey);
    std::cout << "\n";
  }

  // If a battle is triggered and lost, a false value will end the program
  return lootSuccess;
}
