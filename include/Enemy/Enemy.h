#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_H

#include <string>

#include "Player.h"

using std::string;

class Enemy
{
  Enemy(Player *player);
  ~Enemy() { };

protected:
  string name;
  bool boss = false;
  int tier;
  int rewardTier;
  double health;
  double meleeVulnerability;
  double magicVulnerability;
  double rangedVulnerability;

  // ! TODO: unused
  // int attackLow;
  // int attackHigh;
  
  // Helper Functions
  void setEnemyTier(Player *player);
  void setEnemyName(Player *player);
  void setEnemyVulnerabilities();
  void announceEnemy();

public:
  // Mutators
  void receive(Player *player, const string &battleMenuSelection, double playerAttack);
  double attack(int playerArmor);

  // Accessors
  string getName() const { return name; }
  double getHealth() const { return health; }
  double getResistance(Player *player, const string &battleMenuSelection);
  int getTier() const { return tier; }
  int getRewardTier() const { return rewardTier; }

  // Debug
  void debugPrint();
};

#endif //DASTARDLY_DUNGEON_DWELLERS_ENEMY_H