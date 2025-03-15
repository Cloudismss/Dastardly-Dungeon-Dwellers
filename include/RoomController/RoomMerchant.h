#ifndef ROOMMERCHANT_H
#define ROOMMERCHANT_H

#include <string>
#include <vector>

#include "Player.h"

using std::string;
using std::vector;

struct MerchantItem
{
  string name;
  int quantity;
  int cost;
};

void roomMerchant(Player *player);
void roomMerchantPurchase(Player *player, vector<MerchantItem> &shop, const int userShopSelection, int &purchaseAmount);

#endif // ROOMMERCHANT_H
