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
  int tier;
  float health;
  float damage;
  float meleeVulnerability;
  float magicVulnerability;
  float rangedVulnerability;
  int attackLow;
  int attackHigh;

  string generateEnemy();

public:
  // Mutators
  virtual void setEnemyAttributes() = 0;
  void attackEnemy(float attackDamage, const string &attackType);

  // Accessors
  string getName() const { return name; }
  int getTier() const { return tier; }
  float getHealth() const { return health; }
  float attackPlayer() const { return attackLow + (rand() % ((attackHigh + 1) - attackLow)); }
  void announceEnemy();

  // Debug
  void debugPrint();
};

#endif //DASTARDLY_DUNGEON_DWELLERS_ENEMY_H