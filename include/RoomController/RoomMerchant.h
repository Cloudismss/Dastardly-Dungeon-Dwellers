#ifndef ROOMMERCHANT_H
#define ROOMMERCHANT_H

#include <string>
#include <vector>

#include "Player.h"

struct MerchantItem
{
  std::string name;
  int cost;
  int quantity;
};

void roomMerchant(Player *player);
void roomMerchantPurchase(Player *player, std::vector<MerchantItem> &shop, const int userShopSelection, int &purchaseAmount);

#endif // ROOMMERCHANT_H
