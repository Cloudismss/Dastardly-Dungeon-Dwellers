#ifndef DASTARDLY_DUNGEON_DWELLERS_ART_H
#define DASTARDLY_DUNGEON_DWELLERS_ART_H

#include <string>

#include "Enemy.h"
#include "Player.h"

using std::string;

namespace art
{
  namespace battle
  {
    string battleMenu(Player *player, Enemy *enemy);
    void battleHealthArt(const string &className, int playerHealth, const string &enemyName, int enemyHealth);
  }
  namespace box
  {
    void displayMeInABox(const string &message);
    void displayMeInABox(const string &message1, const string &message2);
    void monologueInABox(const string &message);
  }
  namespace room
  {
    void roomEnemyMonologue(const bool ROOM_EXPLORED);
    void roomLootMonologue(const bool ROOM_EXPLORED);
    void roomMerchantMonologue(const bool ROOM_EXPLORED);
    void roomExitMonologue(const bool ROOM_EXPLORED);
  }
  namespace character
  {
    void warriorArt();
    void mageArt();
    void archerArt();
    void bardArt();
  }
  namespace room
  {
    void treasureArt();
    void merchantArt();
    void doorArt();
  }
  namespace game
  {
    void victoryArt(Player *player);
    void gameOverArt(Player *player);
  }
  namespace tutorial
  {
    void tutorialGame();
    void tutorialBattle();
  }
}

#endif // DASTARDLY_DUNGEON_DWELLERS_ART_H
