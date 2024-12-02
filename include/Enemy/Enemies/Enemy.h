#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Enemy
{
public:
  Enemy(short unsigned int playerLevel);
  ~Enemy() { };

public:
  friend std::ostream &operator<<(std::ostream &out, const Enemy &enemy);

protected:
  string name;
  bool boss = false;
  short int health;
  short unsigned int level;
  short unsigned int rewardTier;
  double meleeVulnerability = 1.0;
  double magicVulnerability = 1.0;
  double rangedVulnerability = 1.0;
  
  // Helper Functions
  void setEnemyLevel(short unsigned int playerLevel);
  virtual void announceEnemy();

public:
  // Accessors
  string getName() const { return name; }
  string getNickname() const;
  short int getHealth() const { return health; }
  short unsigned int getLevel() const { return level; }
  short unsigned int getRewardTier() const { return rewardTier; }
  double getVulnerability(const string &battleMenuSelection);

  // Mutators
  void receive(short unsigned int playerAttack);
  short unsigned int attack(short unsigned int playerArmor, short unsigned int playerMaxHealth);
};

#endif // DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
