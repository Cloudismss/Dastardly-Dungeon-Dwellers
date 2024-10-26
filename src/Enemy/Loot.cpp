#include "Loot.h"

#include <iostream>

using std::cout;

void loot(Player *player, Enemy *enemy)
{
  cout << "You check the enemy for valuables:\n";
  int rewardTier = enemy->getRewardTier();
  int lootRoll = 1 + (rand() % 100);

  switch (rewardTier)
  {
    case 1:
    {
      // 10% chance to earn a potion
      if (lootRoll <= 10)
      {
        int potionAdded = 1;
        player->addPotion(potionAdded);
        cout << "Potion added\n";
      }

      // 85% chance to earn a random amount of gold
      if (lootRoll <= 85)
      {
        // Amount of gold returned is between 5-15
        int goldAdded = 5 + (rand() % 11);
        player->addGold(goldAdded);
        cout << "Gold x" << goldAdded << " added\n";
      }

      // Nothing found
      if (lootRoll > 85)
        cout << "You found nothing of value\n";

      cout << "\n";

      break;
    }
    case 2:
    {
      // 30% chance to earn a potion
      if (lootRoll <= 30)
      {
        int potionAdded = 1;
        player->addPotion(potionAdded);
        cout << "Potion added\n";
      }

      // 90% chance to earn a random amount of gold
      if (lootRoll <= 90)
      {
        // Amount of gold returned is between 5-20
        int goldAdded = 5 + (rand() % 16);
        player->addGold(goldAdded);
        cout << "Gold x" << goldAdded << " added\n";
      }

      // Nothing found
      if (lootRoll > 90)
        cout << "You found nothing of value\n";

      cout << "\n";

      break;
    }
    case 3:
    {
      // 60% chance to earn a potion(s)
      if (lootRoll <= 60)
      {
        int potionAdded = 1 + (rand() % 2);
        player->addPotion(potionAdded);
        if (potionAdded == 1)
          cout << "Potion added\n";
        else
          cout << "Potion x" << potionAdded << " added\n";
      }

      // 100% chance to earn a random amount of gold between 10-20
      int goldAdded = 10 + (rand() % 11);
      player->addGold(goldAdded);
      cout << "Gold x" << goldAdded << " added\n";

      cout << "\n";    

      break;
    }
    case 4:
    {
      // 90% chance to earn a potion(s)
      if (lootRoll <= 90)
      {
        int potionAdded = 1 + (rand() % 2);
        player->addPotion(potionAdded);
        if (potionAdded == 1)
          cout << "Potion added\n";
        else
          cout << "Potion x" << potionAdded << " added\n";
      }

      // 100% chance to earn a random amount of gold between 15-20
      int goldAdded = 15 + (rand() % 6);
      player->addGold(goldAdded);
      cout << "Gold x" << goldAdded << " added\n";

      cout << "\n";

      // 5% chance to earn the golden key
      if (lootRoll <= 5)
        player->addKey();

      break;
    }
    case 5:
    {
      // 100% chance to earn a potion(s)
      int potionAdded = 1 + (rand() % 2);
      player->addPotion(potionAdded);
      cout << "Potion x" << potionAdded << " added\n";

      // 100% chance to earn a random amount of gold between 15-20
      int goldAdded = 15 + (rand() % 6);
      player->addGold(goldAdded);
      cout << "Gold x" << goldAdded << " added\n";

      cout << "\n";

      // 15% chance to earn the golden key
      if (lootRoll <= 15)
        player->addKey();

      break;
    }
    case 10:
    {
      // 100% chance to earn 5-10 potions
      int potionAdded = 5 + (rand() % 6);
      player->addPotion(potionAdded);
      cout << "Potion x" << potionAdded << " added\n";

      // 100% chance to earn a random amount of gold between 25-50
      int goldAdded = 25 + (rand() % 26);
      player->addGold(goldAdded);
      cout << "Gold x" << goldAdded << " added\n";

      cout << "\n";

      // 100% chance to earn the golden key
      player->addKey();

      break;
    }
  }
}