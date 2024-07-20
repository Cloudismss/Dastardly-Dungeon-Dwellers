#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_H

#include <iostream>
#include <string>
#include <vector>

#include "Boss.h"
#include "Troll.h"

using std::cerr;
using std::cout;
using std::string;

class Enemy
{
  Enemy();
  ~Enemy();

protected:
  string name;
  bool boss = false;
  int tier;
  int rewardTier;
  double health;
  double damage;
  double meleeVulnerability;
  double magicVulnerability;
  double rangedVulnerability;
  int attackLow;
  int attackHigh;

  string generateEnemy();

public:
  // Mutators
  virtual void setEnemyAttributes() = 0;
  void receive(double healthAdjust, const string &attackType);
  // TODO: Factor in player armor
  double attack(int playerArmor) const { return attackLow + (rand() % ((attackHigh + 1) - attackLow)); }

  // Accessors
  string getName() const { return name; }
  int getTier() const { return tier; }
  double getHealth() const { return health; }
  double getResistance(const string &battleMenuSelection);
  int getRewardTier() const { return rewardTier; }
  void announceEnemy();

  // Debug
  void debugPrint();
};

#endif //DASTARDLY_DUNGEON_DWELLERS_ENEMY_H