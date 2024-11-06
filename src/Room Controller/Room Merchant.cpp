#include "Room Merchant.h"

#include <iomanip>
#include <iostream>

#include "Validation.h"

using std::cin;
using std::cout;
using std::setfill;
using std::setw;

// Pre-condition: called by roomController(), passed inventory variables and className
// Post-condition: Runs merchant shop loop until the player leaves, updates inventory variables
void roomMerchant(Player *player)
{
  // Initialize Merchant Shop arrays
  const string className = player->getClassName();
  vector<MerchantItem> shop;

  // Upgrade variables
  const int KEY_CHANCE = 75;
  const int UPGRADE_CHANCE = 60;
  const int UPGRADE_COST = 50;
  int meleeChance = 1 + rand() % 100;
  int magicChance = 1 + rand() % 100;
  int rangedChance = 1 + rand() % 100;
  int goldenKeyChance = 1 + rand() % 100;

  // Slot 1 - The Merchant has a random number of potions between 2-5
  string potionName = "Potion";
  MerchantItem potion = {potionName, 2 + (rand() % 4), 15};
  shop.push_back(potion);

  // Slot 2 - The Merchant has a random number of armor platings between 1-3
  string armorName = "Armor Plating";
  MerchantItem armor = {armorName, 1 + (rand() % 3), 30};
  shop.push_back(armor);

  // Slot 3 - Melee Upgrade
  string meleeUpgradeName = " ";
  string meleeUpgradeMessage = " ";
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
    MerchantItem melee = {meleeUpgradeName, meleeSuccess, UPGRADE_COST};
    shop.push_back(melee);
  }

  // Slot 4 - Staff Upgrade
  string magicUpgradeName = " ";
  string magicUpgradeMessage = " ";
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
    MerchantItem magic = {magicUpgradeName, magicSuccess, UPGRADE_COST};
    shop.push_back(magic);
  }

  // Slot 5 - Arrow Upgrade
  string rangedUpgradeName = " ";
  string rangedUpgradeMessage = " ";
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
    MerchantItem ranged = {rangedUpgradeName, rangedSuccess, UPGRADE_COST};
    shop.push_back(ranged);
  }

  // Slot 6 - Golden Key
  string keyName = "Golden Key";
  int keySuccess = goldenKeyChance <= KEY_CHANCE;
  if (keySuccess)
  {
    MerchantItem key = {keyName, keySuccess, 100};
    shop.push_back(key);
  }

  // Slot 7 - Exit Index
  string exitName = "Exit";
  MerchantItem exit = {exitName, -1, -1};
  shop.push_back(exit);

  // Loop the shop until the player is ready to leave
  bool shopLoop = true;
  do
  {
    // Display Top Box of Merchant Shop
    string goldDisplay = "Gold: ";
    goldDisplay += std::to_string(player->getGold());
    string potionDisplay = "Potions: ";
    potionDisplay += std::to_string(player->getPotions());
    cout << "." << setfill('-') << setw(63) << ".\n";
    cout << "|" << setfill(' ') << setw(2) << " " << goldDisplay << setw(57 - goldDisplay.length()) << potionDisplay << setw(2) << " " << "|\n";
    cout << "|" << setfill(' ') << setw(63) << "|\n";

    // Print all shop items
    for (int i = 0; i != shop.size(); ++i)
    {
      // Only print the quantity if there are more than one
      if (shop[i].quantity > 1)
      {
        cout << "|" << setw(10) << " " << i + 1 << ". " << shop[i].name << "(s) x" << shop[i].quantity
             << setw(24 - shop[i].name.length()) << " " << "Cost: " << shop[i].cost << setw(14 - std::to_string(shop[i].cost).size()) << "|\n";
      }
      // Don't print the quantity if there's only one
      else if (shop[i].quantity == 1)
      {
        cout << "|" << setw(10) << " " << i + 1 << ". " << shop[i].name
             << setw(30 - shop[i].name.length()) << " " << "Cost: " << shop[i].cost << setw(14 - std::to_string(shop[i].cost).size()) << "|\n";
      }
      // Prints the exit
      else if (shop[i].quantity == -1)
      {
        cout << "|" << setw(10) << " " << i + 1 << ". Exit" << setw(46) << "|\n";
      }
    }

    // Display Bottom Box of Merchant Shop
    cout << "|" << setw(63) << "|\n"
         << "'" << setfill('-') << setw(63) << "'\n"
         << "\n" << setfill(' ');

    // Validate Selection
    int userShopSelection = 0;
    bool loopFlag = true;
    do
    {
      cout << "\tWhat would you like to purchase? ";
      cin >> userShopSelection;
      cout << "\n";
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
          cout << "\tWould you like to buy the golden key for " << shop[userShopSelection].cost << " gold?\n";
          cout << "\tY or N: ";
          cin >> selection;
          cout << "\n";
          if (validateDecision(selection))
            loopFlag = false;
        } while (loopFlag);

        // Player chose to purchase the golden key
        if (selection == 'Y' || selection == 'y')
        {
          shop[userShopSelection].quantity -= 1;
          player->removeGold(shop[userShopSelection].cost);
          player->addKey();
        }
      }
      else
        cout << "\tYou don't have enough gold!\n\n";
    }
    // Player chose to leave
    else if (shop[userShopSelection].name == exitName)
    {
      cout << "\tGoodbye!\n\n";
      shopLoop = false;
    }
    // Proceed with standard transaction - no key or exit
    else if (purchaseAmount > 0)
    {
      // Indent purchase output message
      cout << "\t";

      // Perform transaction
      shop[userShopSelection].quantity -= purchaseAmount;
      player->removeGold(shop[userShopSelection].cost * purchaseAmount);

      // Player chose to buy potions
      if (shop[userShopSelection].name == potionName)
        player->addPotion(purchaseAmount);
      // Player chose to buy armor upgrades
      else if (shop[userShopSelection].name == armorName)
        player->addArmor(purchaseAmount);
      // Player chose to buy the sword upgrade
      else if (shop[userShopSelection].name == meleeUpgradeName)
        player->upgradeWeapon("Melee", meleeUpgradeName);
      // Player chose to buy the magic upgrade
      else if (shop[userShopSelection].name == magicUpgradeName)
        player->upgradeWeapon("Magic", magicUpgradeName);
      // Player chose to buy the ranged upgrade
      else if (shop[userShopSelection].name == rangedUpgradeName)
        player->upgradeWeapon("Ranged", rangedUpgradeName);

      // Add newline to purchase output message
      cout << "\n";
    }

    // Remove empty values from shop vector
    if (shop[userShopSelection].quantity == 0)
    {
      vector<MerchantItem>::iterator iter = shop.begin() + userShopSelection;
      shop.erase(iter);
    }
  } while (shopLoop);

  // Pause the game until the user is ready
  cout << "Press enter to continue to the next room: ";
  string enterKey = " ";
  getline(cin, enterKey);
  cout << "\n";
}

// Pre-condition: called by roomMerchant(), passed item array and item information, along with inventory variables
// Post-condition: asks how many of the item the player would like to buy, checks goldCount to validate purchase, updates purchaseAmount for usage in roomMerchant()
void roomMerchantPurchase(Player *player, vector<MerchantItem> &shop, const int userShopSelection, int &purchaseAmount)
{
  // Validate purchase amount
  bool loopFlag = true;

  // Selected item has >1 qty
  if (shop[userShopSelection].quantity > 1)
  {
    do
    {
      // Ask the player how many items they'd like to buy
      cout << "\t" << shop[userShopSelection].name << "(s) available: " << shop[userShopSelection].quantity << "\n";
      cout << "\tHow many " << shop[userShopSelection].name << "(s) would you like to buy?: ";
      cin >> purchaseAmount;
      cout << "\n";
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
        cout << "\tConfirm purchase of " << purchaseAmount << "x " << shop[userShopSelection].name << " for " << purchaseAmount * shop[userShopSelection].cost << "x Gold?\n";

      // Purchase confirmation without qty printed
      else if (shop[userShopSelection].quantity == 1)
        cout << "\tConfirm purchase of " << shop[userShopSelection].name << " for " << purchaseAmount * shop[userShopSelection].cost << "x Gold?\n";

      cout << "\tY or N: ";
      cin >> merchantConfirm;
      if (validateDecision(merchantConfirm))
      {
        cout << "\n";
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
    cout << "\tYou don't have enough gold!\n\n";
    return;
  }
}