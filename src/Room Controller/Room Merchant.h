#include <iomanip>
#include <iostream>
#include <string>

#include "Upgrade.h"
#include "Validation.h"

using std::cin;
using std::cout;
using std::setfill;
using std::setw;
using std::string;

void roomMerchant(int &potionCount, int &armorCount, int &goldCount, int &keyCount, const string &className);
void roomMerchantPurchase(int ITEM_INDEX, const string merchantItemName[], const int merchantItemQuantity[], const int merchantItemCost[], int &purchaseAmount, int &goldCount);