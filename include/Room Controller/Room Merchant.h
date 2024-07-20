#ifndef DASTARDLY_DUNGEON_DWELLERS_ROOM_MERCHANT_H
#define DASTARDLY_DUNGEON_DWELLERS_ROOM_MERCHANT_H

#include <iomanip>
#include <iostream>
#include <string>

#include "Player.h"
#include "Validation.h"

using std::cin;
using std::cout;
using std::setfill;
using std::setw;
using std::string;

void roomMerchant(Player *player);
void roomMerchantPurchase(Player *player, int ITEM_INDEX, const string merchantItemName[], const int merchantItemQuantity[], const int merchantItemCost[], int &purchaseAmount);

#endif //DASTARDLY_DUNGEON_DWELLERS_ROOM_MERCHANT_H