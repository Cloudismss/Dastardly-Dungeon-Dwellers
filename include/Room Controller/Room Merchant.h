#include <string>

using std::string;

void roomMerchant(int &potionCount, int &armorCount, int &goldCount, int &keyCount, const string &className);
void roomMerchantPurchase(int ITEM_INDEX, const string merchantItemName[], const int merchantItemQuantity[], const int merchantItemCost[], int &purchaseAmount, int &goldCount);