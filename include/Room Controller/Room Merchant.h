#ifndef DASTARDLY_DUNGEON_DWELLERS_ROOM_MERCHANT_H
#define DASTARDLY_DUNGEON_DWELLERS_ROOM_MERCHANT_H

#include <string>

#include "Player.h"

using std::string;

void roomMerchant(Player *player);
void roomMerchantPurchase(Player *player, int ITEM_INDEX, const string merchantItemName[], const int merchantItemQuantity[], const int merchantItemCost[], int &purchaseAmount);

#endif //DASTARDLY_DUNGEON_DWELLERS_ROOM_MERCHANT_H