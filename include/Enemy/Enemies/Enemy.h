#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Enemy
{
public:
  Enemy(int playerLevel);
  ~Enemy() { ++enemyProgression; }

private:
  static inline int enemyProgression = 0;

public:
  static inline int getProgression() { return enemyProgression; }

protected:
  string name;
  bool boss = false;
  int health;
  int level;
  int rewardTier;
  double meleeVulnerability = 1.0;
  double magicVulnerability = 1.0;
  double rangedVulnerability = 1.0;
  
protected:
  // Helper Functions
  void setEnemyLevel(int playerLevel);

public:
  // Accessors
  virtual void announceEnemy() const;
  virtual string getNickname() const { return name; }
  string getName() const { return name; }
  int getHealth() const { return health; }
  int getLevel() const { return level; }
  int getRewardTier() const { return rewardTier; }
  double getVulnerability(const string &battleMenuSelection) const;

  // Mutators
  virtual int attack(int playerArmor, int playerMaxHealth);
  void receive(int playerAttack);
};

#endif // DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
