#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_H

#include <string>

#include "Boss.h"
#include "Troll.h"

using std::string;

class Enemy
{
protected:
  string name;
  string type;
  int tier;
  float health;
  float damage;
  float meleeVulnerability;
  float magicVulnerability;
  float rangedVulnerability;
  int attackLow;
  int attackHigh;

public:
  // Mutators
  virtual void setEnemyAttributes();
  void attackEnemy(float attackDamage, const string &attackType);

  // Accessors
  string getName() const { return name; }
  string getType() const { return type; }
  int getTier() const { return tier; }
  float getHealth() const { return health; }
  float attackPlayer() const { return attackLow + (rand() % ((attackHigh + 1) - attackLow)); }
  void announceEnemy();

  // ! Test
  virtual string getEnemyType() = 0;

  // Debug
  void debugPrint();
};

#endif //DASTARDLY_DUNGEON_DWELLERS_ENEMY_H