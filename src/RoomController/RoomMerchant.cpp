#include "RoomMerchant.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "Globals.h"
#include "Validation.h"

void roomMerchant(Player *player)
{
  // Initialize Merchant Shop arrays
  const std::string className = player->getCharacter()->getClassName();
  std::vector<MerchantItem> shop;
  shop.reserve(6);

  // Upgrade variables
  const int KEY_CHANCE = 75;
  const int UPGRADE_CHANCE = 60;
  const int UPGRADE_COST = 50;
  int meleeChance = 1 + rand() % 100;
  int magicChance = 1 + rand() % 100;
  int rangedChance = 1 + rand() % 100;
  int goldenKeyChance = 1 + rand() % 100;

  // Slot 1 - The Merchant has a random number of potions between 2-5
  std::string potionName = "Potion";
  MerchantItem potion = {potionName, 15, 2 + (rand() % 4)};
  shop.emplace_back(potion);

  // Slot 2 - The Merchant has a random number of armor platings between 1-3
  std::string armorName = "Armor Plating";
  MerchantItem armor = {armorName, 30, 1 + (rand() % 3)};
  shop.emplace_back(armor);

  // Slot 3 - Melee Upgrade
  std::string meleeUpgradeName = " ";
  std::string meleeUpgradeMessage = " ";
  int meleeSuccess = meleeChance <= UPGRADE_CHANCE;
  if (meleeSuccess)
  {
    if (className == "Warrior")
    {
      meleeUpgradeName = "Sword Sharpening";
      meleeUpgradeMessage = "\tYou feel an immense power emanating from your blade\n";
    }
    else if (className == "Mage")
    {
      meleeUpgradeName = "Staff Density";
      meleeUpgradeMessage = "\tThe weight of a distant star infuses within your staff\n";
    }
    else if (className == "Archer")
    {
      meleeUpgradeName = "Honed Blades";
      meleeUpgradeMessage = "\tYour blades shimmer a soft blue gleam, there may be enemies nearby\n";
    }
    else if (className == "Bard")
    {
      meleeUpgradeName = "Lute Polish";
      meleeUpgradeMessage = "\tYour lute gently tugs on your shoulder, politely yearning for your affection\n";
    }
    meleeUpgradeMessage += "\tYour melee damage has been upgraded!\n\n";
    MerchantItem melee = {meleeUpgradeName, UPGRADE_COST, meleeSuccess};
    shop.emplace_back(melee);
  }

  // Slot 4 - Staff Upgrade
  std::string magicUpgradeName = " ";
  std::string magicUpgradeMessage = " ";
  int magicSuccess = magicChance <= UPGRADE_CHANCE;
  if (magicSuccess)
  {
    if (className == "Warrior")
    {
      magicUpgradeName = "Shield Polish";
      magicUpgradeMessage = "\tYour shield shakes with vicious ferocity, it is ready to bash your foes\n";
    }
    else if (className == "Mage")
    {
      magicUpgradeName = "Runald's Ice Band";
      magicUpgradeMessage = "\tA soft implosion pops within your staff, you feel empowered by the spirits of the dungeon\n";
    }
    else if (className == "Archer")
    {
      magicUpgradeName = "Toxic Canister";
      magicUpgradeMessage = "\tYour toxins breathe a voracious pestilence, suffocating your enemies\n";
    }
    else if (className == "Bard")
    {
      magicUpgradeName = "Throat Lubricant";
      magicUpgradeMessage = "\tYour throat feels nice and refreshed\n";
    }
    magicUpgradeMessage += "\tYour magic damage has been upgraded!\n\n";
    MerchantItem magic = {magicUpgradeName, UPGRADE_COST, magicSuccess};
    shop.emplace_back(magic);
  }

  // Slot 5 - Ranged Upgrade
  std::string rangedUpgradeName = " ";
  std::string rangedUpgradeMessage = " ";
  int rangedSuccess = rangedChance <= UPGRADE_CHANCE;
  if (rangedSuccess)
  {
    if (className == "Warrior")
    {
      rangedUpgradeName = "Titanium Throwing Sleeve";
      rangedUpgradeMessage = "\tYour spear calls for your grasp, ready to soar with reckless ferocity\n";
    }
    else if (className == "Mage")
    {
      rangedUpgradeName = "Static Cleanse";
      rangedUpgradeMessage = "\tA mystical cloud descends upon you, relieving you of your static charge\n";
    }
    else if (className == "Archer")
    {
      rangedUpgradeName = "Arcane Arrow Treatment";
      rangedUpgradeMessage = "\tYour quiver shakes ferociously, you knock your bow with fearless determination\n";
    }
    else if (className == "Bard")
    {
    rangedUpgradeName = "Chapstick";
    rangedUpgradeMessage = "\tThe air in this dungeon is very dry, you'll certainly need this\n";
    }
    rangedUpgradeMessage += "\tYour ranged damage has been upgraded!\n\n";
    MerchantItem ranged = {rangedUpgradeName, UPGRADE_COST, rangedSuccess};
    shop.emplace_back(ranged);
  }

  // Slot 6 - Golden Key
  std::string keyName = "Golden Key";
  int keySuccess = goldenKeyChance <= KEY_CHANCE;
  if (keySuccess)
  {
    MerchantItem key = {keyName, 100, keySuccess};
    shop.emplace_back(key);
  }

  // Slot 7 - Exit Index
  std::string exitName = "Exit";
  MerchantItem exit = {exitName, 1, -1};
  shop.emplace_back(exit);

  // Loop the shop until the player is ready to leave
  bool shopLoop = true;
  do
  {
    // Display Top Box of Merchant Shop
    std::string goldDisplay = "Gold: ";
    goldDisplay += std::to_string(player->getGold());
    std::string potionDisplay = "Potions: ";
    potionDisplay += std::to_string(player->getPotions());
    std::cout << "." << std::setfill('-') << std::setw(63) << ".\n";
    std::cout << "|" << std::setfill(' ') << std::setw(2) << " " << goldDisplay << std::setw(57 - goldDisplay.length()) << potionDisplay << std::setw(2) << " " << "|\n";
    std::cout << "|" << std::setfill(' ') << std::setw(63) << "|\n";

    // Print all shop items
    for (int i = 0; i != shop.size(); ++i)
    {
      // Only print the quantity if there are more than one
      if (shop[i].quantity > 1)
      {
        std::cout << "|" << std::setw(10) << " " << i + 1 << ": " << shop[i].name << "(s) x" << shop[i].quantity
             << std::setw(24 - shop[i].name.length()) << " " << "Cost: " << shop[i].cost << std::setw(14 - std::to_string(shop[i].cost).size()) << "|\n";
      }
      // Don't print the quantity if there's only one
      else if (shop[i].quantity == 1)
      {
        std::cout << "|" << std::setw(10) << " " << i + 1 << ": " << shop[i].name
             << std::setw(30 - shop[i].name.length()) << " " << "Cost: " << shop[i].cost << std::setw(14 - std::to_string(shop[i].cost).size()) << "|\n";
      }
      // Prints the exit last
      else if (shop[i].quantity == -1)
      {
        std::cout << "|" << std::setw(10) << " " << i + 1 << ": Exit" << std::setw(46) << "|\n";
      }
    }

    // Display Bottom Box of Merchant Shop
    std::cout << "|" << std::setw(63) << "|\n"
         << "'" << std::setfill('-') << std::setw(63) << "'\n"
         << "\n" << std::setfill(' ');

    // Validate Selection
    int userShopSelection = 0;
    bool loopFlag = true;
    do
    {
      std::cout << "\tWhat would you like to purchase? ";
      std::cin >> userShopSelection;
      std::cout << "\n";
      if (validateInput(userShopSelection, 1, shop.size()))
        loopFlag = false;
    } while (loopFlag);

    // Translate selection to index values
    userShopSelection -= 1;

    // Variable to hold amount of items to purchase
    int purchaseAmount = 0;

    // Call purchase function on everything but the key and exit
    if (shop[userShopSelection].quantity > 0 && shop[userShopSelection].name != keyName && shop[userShopSelection].name != exitName)
      roomMerchantPurchase(player, shop, userShopSelection, purchaseAmount);

    // Player chose to purchase the key
    if (shop[userShopSelection].name == keyName)
    {
      // Make sure the player has enough gold
      if (player->getGold() >= shop[userShopSelection].cost)
      {
        // Validate selection
        char selection = ' ';
        loopFlag = true;
        do
        {
          std::cout << "\tWould you like to buy the golden key for " << shop[userShopSelection].cost << " gold?\n";
          std::cout << "\tY or N: ";
          std::cin >> selection;
          std::cout << "\n";
          if (validateDecision(selection))
            loopFlag = false;
        } while (loopFlag);

        // Player chose to purchase the golden key
        if (selection == 'Y' || selection == 'y')
        {
          shop[userShopSelection].quantity -= 1;
          player->removeGold(shop[userShopSelection].cost);
          player->addKeys(1);
        }
      }
      else
        std::cout << "\tYou don't have enough gold!\n\n";
    }
    // Player chose to leave
    else if (shop[userShopSelection].name == exitName)
    {
      std::cout << "\tGoodbye!\n\n";
      shopLoop = false;
    }
    // Proceed with standard transaction - no key or exit
    else if (purchaseAmount > 0)
    {
      // Indent purchase output message
      std::cout << "\t";

      // Perform transaction
      shop[userShopSelection].quantity -= purchaseAmount;
      player->removeGold(shop[userShopSelection].cost * purchaseAmount);

      // Player chose to buy potions
      if (shop[userShopSelection].name == potionName)
        player->addPotions(purchaseAmount);
      // Player chose to buy armor upgrades
      else if (shop[userShopSelection].name == armorName)
        player->addArmor(purchaseAmount);
      // Player chose to buy the sword upgrade
      else if (shop[userShopSelection].name == meleeUpgradeName)
        player->getCharacter()->upgradeWeapon(skill::MELEE, meleeUpgradeName);
      // Player chose to buy the magic upgrade
      else if (shop[userShopSelection].name == magicUpgradeName)
        player->getCharacter()->upgradeWeapon(skill::MAGIC, magicUpgradeName);
      // Player chose to buy the ranged upgrade
      else if (shop[userShopSelection].name == rangedUpgradeName)
        player->getCharacter()->upgradeWeapon(skill::RANGED, rangedUpgradeName);

      // Add newline to purchase output message
      std::cout << "\n";
    }

    // Remove empty values from shop std::vector
    if (shop[userShopSelection].quantity == 0)
    {
      std::vector<MerchantItem>::iterator iter = shop.begin() + userShopSelection;
      shop.erase(iter);
    }
  } while (shopLoop);

  // Pause the game until the user is ready
  std::cout << "Press enter to continue to the next room: ";
  std::string enterKey = " ";
  getline(std::cin, enterKey);
  std::cout << "\n";
}

void roomMerchantPurchase(Player *player, std::vector<MerchantItem> &shop, const int userShopSelection, int &purchaseAmount)
{
  // Validate purchase amount
  bool loopFlag = true;

  // Selected item has >1 qty
  if (shop[userShopSelection].quantity > 1)
  {
    do
    {
      std::cout << "\t" << shop[userShopSelection].name << "(s) available: " << shop[userShopSelection].quantity << "\n";
      std::cout << "\tHow many " << shop[userShopSelection].name << "(s) would you like to buy?: ";
      std::cin >> purchaseAmount;
      std::cout << "\n";
      if (validateInput(purchaseAmount, 0, shop[userShopSelection].quantity))
      {
        loopFlag = false;

        // If they choose 0, exit purchase menu
        if (purchaseAmount == 0)
          return;
      }
    } while (loopFlag);
  }

  // Selected item has 1 remaining qty
  else if (shop[userShopSelection].quantity == 1)
    purchaseAmount = 1;

  // Make sure the player has enough gold for the purchase
  if (player->getGold() >= purchaseAmount * shop[userShopSelection].cost)
  {
    // Purchase confirmation loop
    char merchantConfirm = ' ';
    loopFlag = true;
    do
    {
      // Purchase confirmation with qty printed
      if (shop[userShopSelection].quantity > 1)
        std::cout << "\tConfirm purchase of " << purchaseAmount << "x " << shop[userShopSelection].name << " for " << purchaseAmount * shop[userShopSelection].cost << "x Gold?\n";

      // Purchase confirmation without qty printed
      else if (shop[userShopSelection].quantity == 1)
        std::cout << "\tConfirm purchase of " << shop[userShopSelection].name << " for " << purchaseAmount * shop[userShopSelection].cost << "x Gold?\n";

      std::cout << "\tY or N: ";
      std::cin >> merchantConfirm;
      if (validateDecision(merchantConfirm))
      {
        std::cout << "\n";
        loopFlag = false;
      }
    } while (loopFlag);

    // Player chose not to purchase the item
    if (merchantConfirm == 'N' || merchantConfirm == 'n')
      purchaseAmount = 0;
  }

  // Player couldn't afford the purchase
  else
  {
    purchaseAmount = 0;
    std::cout << "\tYou don't have enough gold!\n\n";
    return;
  }
}
