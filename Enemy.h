#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_H

#include "Dastardly Dungeon Dwellers.h"
#include "Progression.h"

class Enemy
{
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

public:
  // Mutators
  virtual void setEnemyAttributes();
  void attackEnemy(float attackDamage, const string &attackType);

  // Accessors
  string getName() const { return name; }
  int getTier() const { return tier; }
  float getHealth() const { return health; }
  float attackPlayer() const { return attackLow + (rand() % ((attackHigh + 1) - attackLow)); }
  virtual void announceEnemy();

  // Debug
  void debugPrint();
};

class Troll: public Enemy
{
  void setEnemyAttributes() override;
  void announceEnemy() override;
};

class Boss: public Enemy
{
  void setEnemyAttributes() override;
  void announceEnemy() override;
};

#endif //DASTARDLY_DUNGEON_DWELLERS_ENEMY_H