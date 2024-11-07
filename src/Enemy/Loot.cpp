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
        player->addPotion(1);

      // 85% chance to earn a random amount of gold between 5-15
      if (lootRoll <= 85)
        player->addGold(5 + (rand() % 11));

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
        player->addPotion(1);

      // 90% chance to earn a random amount of gold between 5-20
      if (lootRoll <= 90)
        player->addGold(5 + (rand() % 16));

      // Nothing found
      if (lootRoll > 90)
        cout << "You found nothing of value\n";

      cout << "\n";

      break;
    }
    case 3:
    {
      // 60% chance to earn a potion(s) between 1 and 2
      if (lootRoll <= 60)
        player->addPotion(1 + (rand() % 2));

      // 100% chance to earn a random amount of gold between 10-20
      player->addGold(10 + (rand() % 11));

      cout << "\n";    

      break;
    }
    case 4:
    {
      // 90% chance to earn a potion(s) between 1 and 2
      if (lootRoll <= 90)
        player->addPotion(1 + (rand() % 2));

      // 100% chance to earn a random amount of gold between 15-20
      player->addGold(15 + (rand() % 6));

      cout << "\n";

      // 5% chance to earn the golden key
      if (lootRoll <= 5)
        player->addKey();

      break;
    }
    case 5:
    {
      // 100% chance to earn a potion(s) between 1 and 2
      player->addPotion(1 + (rand() % 2));

      // 100% chance to earn a random amount of gold between 15-20
      player->addGold(15 + (rand() % 6));

      cout << "\n";

      // 15% chance to earn the golden key
      if (lootRoll <= 15)
        player->addKey();

      break;
    }
    case 10:
    {
      // 100% chance to earn 5-10 potions
      player->addPotion(5 + (rand() % 6));

      // 100% chance to earn a random amount of gold between 25-50
      player->addGold(25 + (rand() % 26));

      cout << "\n";

      // 100% chance to earn the golden key
      player->addKey();

      break;
    }
  }
}
