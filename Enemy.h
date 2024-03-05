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
  float resistance;

public:
  // Mutators
  void setEnemyAttributes();
  void attackEnemy(float damage);

  // Accessors
  string getName() const;
  int getTier() const;
  float getHealth() const;
  float attackPlayer() const;
  float getResistance() const;
};

class Troll: public Enemy
{

};

class Boss: public Enemy
{

};

void classTester();
void inSomeFunction();
void generateEnemy(Progression &, Enemy &);

#endif //DASTARDLY_DUNGEON_DWELLERS_ENEMY_H