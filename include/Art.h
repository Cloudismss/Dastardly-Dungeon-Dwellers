#ifndef DASTARDLY_DUNGEON_DWELLERS_ART_H
#define DASTARDLY_DUNGEON_DWELLERS_ART_H

#include <string>

#include "Enemy.h"
#include "Player.h"

using std::string;

string battleMenu(Player *player, Enemy *enemy);
void battleHealthArt(int playerHealth, int enemyHealth);
void displayMeInABox(const string &message);
void displayMeInABox(const string &message1, const string &message2);
void monologueInABox (const string &message);
void roomEnemyMonologue(const bool ROOM_EXPLORED);
void roomLootMonologue(const bool ROOM_EXPLORED);
void roomMerchantMonologue(const bool ROOM_EXPLORED);
void roomExitMonologue(const bool ROOM_EXPLORED);
void warriorArt();
void mageArt();
void archerArt();
void bardArt();
void treasureArt();
void merchantArt();
void doorArt();
void victoryArt(Player *player);
void gameOverArt(Player *player);
void tutorialGame();
void tutorialBattle();

#endif //DASTARDLY_DUNGEON_DWELLERS_ART_H
