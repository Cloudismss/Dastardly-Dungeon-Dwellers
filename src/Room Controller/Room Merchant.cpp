#include "Room Merchant.h"

// Pre-condition: called by roomController(), passed inventory variables and className
// Post-condition: Runs merchant shop loop until the player leaves, updates inventory variables
void roomMerchant(int &potionCount, int &armorCount, int &goldCount, int &keyCount, const string &className)
{
  // Initialize Merchant Shop arrays
  const int NUM_ITEMS = 7 + 1; // Adding one here so the visual menu matches index location, we're not using index 0. (Wasteful, but it really helped me visualize the shop output) - Refactor
  int merchantItemQuantity[NUM_ITEMS] = {0};
  int merchantItemCost[NUM_ITEMS] = {0};
  string merchantItemName[NUM_ITEMS];
  for (int i = 0; i < NUM_ITEMS; ++i)
  {
    merchantItemName[i] = " ";
  }

  // shopItemIndex array variable is used only to aid in translating user input indexes to 1-6 in numberTranslated loop. We need this since the shop is randomized
  int shopItemIndex[NUM_ITEMS] = {0};
  for (int i = 1; i < NUM_ITEMS; ++i)
  {
    shopItemIndex[i] = i;
  }

  // Upgrade variables
  const int MELEE_WEAPON = 0, MAGIC_WEAPON = 1, RANGED_WEAPON = 2;
  const int KEY_CHANCE = 75;
  const int UPGRADE_CHANCE = 60;
  const int UPGRADE_COST = 50;
  int meleeChance = 1 + rand() % 100;
  int magicChance = 1 + rand() % 100;
  int rangedChance = 1 + rand() % 100;
  int goldenKeyChance = 1 + rand() % 100;

  // Slot 1 - The Merchant has a random number of potions between 2-5
  const int POTION_INDEX = 1;
  merchantItemName[POTION_INDEX] = "Potion";
  merchantItemQuantity[POTION_INDEX] = 2 + (rand() % 4);
  merchantItemCost[POTION_INDEX] = 15;

  // Slot 2 - The Merchant has a random number of armor platings between 1-3
  const int ARMOR_UPGRADE_INDEX = 2;
  merchantItemName[ARMOR_UPGRADE_INDEX] = "Armor Plating";
  merchantItemQuantity[ARMOR_UPGRADE_INDEX] = 1 + (rand() % 3);
  merchantItemCost[ARMOR_UPGRADE_INDEX] = 30;

  // Slot 3 - Melee Upgrade
  const int MELEE_UPGRADE_INDEX = 3;
  if (className == "Warrior")
  {
    merchantItemName[MELEE_UPGRADE_INDEX] = "Sword Sharpening";
  }
  else if (className == "Mage")
  {
    merchantItemName[MELEE_UPGRADE_INDEX] = "Staff Density";
  }
  else if (className == "Archer")
  {
    merchantItemName[MELEE_UPGRADE_INDEX] = "Honed Blades";
  }
  else if (className == "Bard")
  {
    merchantItemName[MELEE_UPGRADE_INDEX] = "Lute Polish";
  }
  merchantItemQuantity[MELEE_UPGRADE_INDEX] = 0;
  merchantItemCost[MELEE_UPGRADE_INDEX] = UPGRADE_COST;

  // Slot 4 - Staff Upgrade
  const int MAGIC_UPGRADE_INDEX = 4;
  if (className == "Warrior")
  {
    merchantItemName[MAGIC_UPGRADE_INDEX] = "Shield Polish";
  }
  else if (className == "Mage")
  {
    merchantItemName[MAGIC_UPGRADE_INDEX] = "Runald's Ice Band";
  }
  else if (className == "Archer")
  {
    merchantItemName[MAGIC_UPGRADE_INDEX] = "Toxic Canister";
  }
  else if (className == "Bard")
  {
    merchantItemName[MAGIC_UPGRADE_INDEX] = "Throat Lubricant";
  }
  merchantItemQuantity[MAGIC_UPGRADE_INDEX] = 0;
  merchantItemCost[MAGIC_UPGRADE_INDEX] = UPGRADE_COST;

  // Slot 5 - Arrow Upgrade
  const int RANGED_UPGRADE_INDEX = 5;
  if (className == "Warrior")
  {
    merchantItemName[RANGED_UPGRADE_INDEX] = "Titanium Throwing Sleeve";
  }
  else if (className == "Mage")
  {
    merchantItemName[RANGED_UPGRADE_INDEX] = "Static Cleanse";
  }
  else if (className == "Archer")
  {
    merchantItemName[RANGED_UPGRADE_INDEX] = "Arcane Arrow Treatment";
  }
  else if (className == "Bard")
  {
    merchantItemName[RANGED_UPGRADE_INDEX] = "Chapstick";
  }
  merchantItemQuantity[RANGED_UPGRADE_INDEX] = 0;
  merchantItemCost[RANGED_UPGRADE_INDEX] = UPGRADE_COST;

  // Slot 6 - Golden Key
  const int GOLDEN_KEY_INDEX = NUM_ITEMS - 2;
  merchantItemName[GOLDEN_KEY_INDEX] = "Golden Key";
  merchantItemQuantity[GOLDEN_KEY_INDEX] = 0;
  merchantItemCost[GOLDEN_KEY_INDEX] = 100;

  // Slot 7 - Exit Index
  const int EXIT_INDEX = NUM_ITEMS - 1;
  merchantItemName[EXIT_INDEX] = "Exit";
  merchantItemQuantity[EXIT_INDEX] = 1;

  // Shop position tracking array, only used for translating positions in switch statement
  string shopItemOrder[NUM_ITEMS];
  for (int i = 0; i < NUM_ITEMS; ++i)
  {
    shopItemOrder[i] = " ";
  }

  // Chance to sell melee upgrade
  if (meleeChance <= UPGRADE_CHANCE)
  {
    merchantItemQuantity[MELEE_UPGRADE_INDEX] = 1;
  }

  // Chance to sell magic upgrade
  if (magicChance <= UPGRADE_CHANCE)
  {
    merchantItemQuantity[MAGIC_UPGRADE_INDEX] = 1;
  }

  // Chance to sell ranged upgrade
  if (rangedChance <= UPGRADE_CHANCE)
  {
    merchantItemQuantity[RANGED_UPGRADE_INDEX] = 1;
  }

  // Chance to sell golden key
  if (goldenKeyChance <= KEY_CHANCE)
  {
    merchantItemQuantity[GOLDEN_KEY_INDEX] = 1;
  }

  // Loop the shop until the player is ready to leave
  bool shopLoop = true;
  do
  {
    // Display Top Box of Merchant Shop
    string goldDisplay = "Gold: ";
    goldDisplay += std::to_string(goldCount);
    string potionDisplay = "Potions: ";
    potionDisplay += std::to_string(potionCount);
    cout << "." << setfill('-') << setw(63) << ".\n";
    cout << "|" << setfill(' ') << setw(2) << " " << goldDisplay << setw(57 - goldDisplay.length()) << potionDisplay << setw(2) << " " << "|\n";
    cout << "|" << setfill(' ') << setw(63) << "|\n";

    // Counter to hold amount of items/lines to be displayed
    int shopItemCount = 0;

    // Display middle rows - randomized shop items
    for (int i = 1; i < NUM_ITEMS; ++i)
    {
      // Print all shop items except for exit
      if (i < EXIT_INDEX)
      {
        // Only list items that are for sale
        if (merchantItemQuantity[i] > 0)
        {
          // Only print the quantity if there are more than one
          if (merchantItemQuantity[i] > 1)
          {
            cout << "|" << setw(10) << " " << ++shopItemCount << ". " << merchantItemName[i] << "(s) x" << merchantItemQuantity[i]
                 << setw(24 - merchantItemName[i].length()) << " " << "Cost: " << merchantItemCost[i] << setw(14 - std::to_string(merchantItemCost[i]).size()) << "|\n";
          }
          // Don't print the quantity if there's only one
          else if (merchantItemQuantity[i] == 1)
          {
            cout << "|" << setw(10) << " " << ++shopItemCount << ". " << merchantItemName[i]
                 << setw(30 - merchantItemName[i].length()) << " " << "Cost: " << merchantItemCost[i] << setw(14 - std::to_string(merchantItemCost[i]).size()) << "|\n";
          }
          // Places item name values in shopItemOrder array
          shopItemOrder[shopItemCount] = merchantItemName[i];
        }
      }
      // Prints the exit
      else if (i == EXIT_INDEX)
      {
       cout << "|" << setw(10) << " " << ++shopItemCount << ". Exit" << setw(46) << "|\n";
       // Places item name values in shopItemOrder array
       shopItemOrder[shopItemCount] = merchantItemName[i];
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
      if (validateInput(userShopSelection, 1, shopItemCount))
      {
        loopFlag = false;
      }
    } while (loopFlag);

    // Translate userShopSelection to a value matching original indexes 1-6 for usage in switch statement
    bool numberTranslated = false;
    int loopCount = 1;
    do
    {
      if (shopItemOrder[userShopSelection] == merchantItemName[loopCount])
      {
        userShopSelection = shopItemIndex[loopCount];
        numberTranslated = true;
      }
      ++loopCount;
    } while (!numberTranslated);

    // Switch player purchase choice
    int purchaseAmount = 0;
    switch (userShopSelection)
    {
      // Player chose to buy potions
      case POTION_INDEX:
      {
        roomMerchantPurchase(POTION_INDEX, merchantItemName, merchantItemQuantity, merchantItemCost, purchaseAmount,goldCount);
        if (purchaseAmount > 0)
        {
          merchantItemQuantity[POTION_INDEX] -= purchaseAmount;
          goldCount -= merchantItemCost[POTION_INDEX] * purchaseAmount;
          potionCount += purchaseAmount;
        }
        break;
      }

      // Player chose to buy armor upgrades
      case ARMOR_UPGRADE_INDEX:
      {
        roomMerchantPurchase(ARMOR_UPGRADE_INDEX, merchantItemName, merchantItemQuantity, merchantItemCost, purchaseAmount,goldCount);
        if (purchaseAmount > 0)
        {
          merchantItemQuantity[ARMOR_UPGRADE_INDEX] -= purchaseAmount;
          goldCount -= merchantItemCost[ARMOR_UPGRADE_INDEX] * purchaseAmount;
          armorCount += purchaseAmount;
        }
        break;
      }

      // Player chose to buy the sword upgrade
      case MELEE_UPGRADE_INDEX:
      {
        roomMerchantPurchase(MELEE_UPGRADE_INDEX, merchantItemName, merchantItemQuantity, merchantItemCost, purchaseAmount, goldCount);
        if (purchaseAmount > 0)
        {
          if (className == "Warrior")
          {
            cout << "\tYou feel an immense power emanating from your blade\n";
          }
          else if (className == "Mage")
          {
            cout << "\tThe weight of a distant star infuses within your staff\n";
          }
          else if (className == "Archer")
          {
            cout << "\tYour blades shimmer a soft blue gleam, there may be enemies nearby\n";
          }
          else if (className == "Bard")
          {
            cout << "\tYour lute gently tugs on your shoulder, politely yearning for your affection\n";
          }
          cout <<  "\tYour melee damage has been upgraded!\n\n";
          merchantItemQuantity[MELEE_UPGRADE_INDEX] -= purchaseAmount;
          goldCount -= merchantItemCost[MELEE_UPGRADE_INDEX] * purchaseAmount;
          weaponUpgrade(0, MELEE_WEAPON);
        }
        break;
      }

      // Player chose to buy the magic upgrade
      case MAGIC_UPGRADE_INDEX:
      {
        roomMerchantPurchase(MAGIC_UPGRADE_INDEX, merchantItemName, merchantItemQuantity, merchantItemCost, purchaseAmount, goldCount);
        if (purchaseAmount > 0)
        {
          if (className == "Warrior")
          {
            cout << "\tYour shield shakes with vicious ferocity, it is ready to bash your foes\n";
          }
          else if (className == "Mage")
          {
            cout << "\tA soft implosion pops within your staff, you feel empowered by the spirits of the dungeon\n";
          }
          else if (className == "Archer")
          {
            cout << "\tYour toxins breathe a voracious pestilence, suffocating your enemies\n";
          }
          else if (className == "Bard")
          {
            cout << "\tYour throat feels nice and refreshed\n";
          }
          cout <<  "\tYour magic damage has been upgraded!\n\n";
          merchantItemQuantity[MAGIC_UPGRADE_INDEX] -= purchaseAmount;
          goldCount -= merchantItemCost[MAGIC_UPGRADE_INDEX] * purchaseAmount;
          weaponUpgrade(0, MAGIC_WEAPON);
        }
        break;
      }

      // Player chose to buy the ranged upgrade
      case RANGED_UPGRADE_INDEX:
      {
        roomMerchantPurchase(RANGED_UPGRADE_INDEX, merchantItemName, merchantItemQuantity, merchantItemCost, purchaseAmount, goldCount);
        if (purchaseAmount > 0)
        {
          if (className == "Warrior")
          {
            cout << "\tYour spear calls for your grasp, ready to soar with reckless ferocity\n";
          }
          else if (className == "Mage")
          {
            cout << "\tA mystical cloud descends upon you, relieving you of your static charge\n";
          }
          else if (className == "Archer")
          {
            cout << "\tYour quiver shakes ferociously, you knock your bow with fearless determination\n";
          }
          else if (className == "Bard")
          {
            cout << "\tThe air in this dungeon is very dry, you'll certainly need this\n";
          }
          cout <<  "\tYour ranged damage has been upgraded!\n\n";
          merchantItemQuantity[RANGED_UPGRADE_INDEX] -= purchaseAmount;
          goldCount -= merchantItemCost[RANGED_UPGRADE_INDEX] * purchaseAmount;
          weaponUpgrade(0, RANGED_WEAPON);
        }
        break;
      }

      // Player chose to purchase the golden key
      case GOLDEN_KEY_INDEX:
      {
        // Make sure the player has enough gold
        if (goldCount >= merchantItemCost[GOLDEN_KEY_INDEX])
        {
          // Validate selection
          char selection = ' ';
          loopFlag = true;
          do
          {
            cout << "\tWould you like to buy the golden key for " << merchantItemCost[GOLDEN_KEY_INDEX] << " gold?\n";
            cout << "\tY or N: ";
            cin >> selection;
            cout << "\n";
            if (validateDecision(selection))
            {
              loopFlag = false;
            }
          } while (loopFlag);

          // Player chose to purchase the golden key
          if (selection == 'Y' || selection == 'y')
          {
            merchantItemQuantity[GOLDEN_KEY_INDEX] -= 1;
            goldCount -= merchantItemCost[GOLDEN_KEY_INDEX];
            ++keyCount;
            cout << "\t." << setfill('-') << setw(46) << ".\n"
                 << "\t|" << setfill(' ') << setw(46) << "|\n"
                 << "\t|" << setw(12) << " " << "GOLDEN KEY acquired!" << setw(11) << " " << " |\n"
                 << "\t|" << setfill(' ') << setw(46) << "|\n"
                 << "\t'" << setfill('-') << setw(46) << "'\n"
                 << "\n";
          }
        }

        // Player doesn't have enough gold
        else
        {
          cout << "\tYou don't have enough gold!\n\n";
        }
        break;
      }

      // Player chose to leave
      case EXIT_INDEX:
      {
        cout << "\tGoodbye!\n\n";
        shopLoop = false;
        break;
      }
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
void roomMerchantPurchase(int ITEM_INDEX, const string merchantItemName[], const int merchantItemQuantity[], const int merchantItemCost[], int &purchaseAmount, int &goldCount)
{
  // Validate purchase amount
  bool loopFlag = true;

  // Selected item has >1 qty
  if (merchantItemQuantity[ITEM_INDEX] > 1)
  {
    do
    {
      // Ask the player how many items they'd like to buy
      cout << "\t" << merchantItemName[ITEM_INDEX] << "(s) available: " << merchantItemQuantity[ITEM_INDEX] << "\n";
      cout << "\tHow many " << merchantItemName[ITEM_INDEX] << "(s) would you like to buy?: ";
      cin >> purchaseAmount;
      cout << "\n";
      if (validateInput(purchaseAmount, 0, merchantItemQuantity[ITEM_INDEX]))
      {
        loopFlag = false;

        // If they choose 0, exit purchase menu
        if (purchaseAmount == 0)
        {
          return;
        }
      }
    } while (loopFlag);
  }

  // Selected item has 1 remaining qty
  else if (merchantItemQuantity[ITEM_INDEX] == 1)
  {
    purchaseAmount = 1;
  }

  // Selected item has 0 remaining qty
  else if (merchantItemQuantity[ITEM_INDEX] == 0)
  {
    purchaseAmount = 0;
    cout << "\tI'm fresh out of that item, check back later\n\n";
    return;
  }

  // Make sure the player has enough gold for the purchase
  if (goldCount >= purchaseAmount * merchantItemCost[ITEM_INDEX])
  {
    // Purchase confirmation loop
    char merchantConfirm = ' ';
    loopFlag = true;
    do
    {
      // Purchase confirmation with qty printed
      if (merchantItemQuantity[ITEM_INDEX] > 1)
      {
        cout << "\tConfirm purchase of " << purchaseAmount << "x " << merchantItemName[ITEM_INDEX] << " for x" << purchaseAmount * merchantItemCost[ITEM_INDEX] << " gold?\n";
      }

      // Purchase confirmation without qty printed
      else if (merchantItemQuantity[ITEM_INDEX] == 1)
      {
        cout << "\tConfirm purchase of " << merchantItemName[ITEM_INDEX] << " for x" << purchaseAmount * merchantItemCost[ITEM_INDEX] << " gold?\n";
      }

      cout << "\tY or N: ";
      cin >> merchantConfirm;
      if (validateDecision(merchantConfirm))
      {
        cout << "\n";
        loopFlag = false;
      }
    } while (loopFlag);

    // Player chose to purchase the item
    if (merchantConfirm == 'Y' || merchantConfirm == 'y')
    {
      if (merchantItemQuantity[ITEM_INDEX] > 1)
      {
        cout << "\t" << merchantItemName[ITEM_INDEX] << " x" << purchaseAmount << " acquired!\n\n";
      }
      else
      {
        cout << "\t" << merchantItemName[ITEM_INDEX] << " acquired!\n\n";
      }
    }

    // Player chose not to purchase the item
    else
    {
      purchaseAmount = 0;
    }
  }

  // Player couldn't afford the purchase
  else
  {
    purchaseAmount = 0;
    cout << "\tYou don't have enough gold!\n\n";
    return;
  }
}