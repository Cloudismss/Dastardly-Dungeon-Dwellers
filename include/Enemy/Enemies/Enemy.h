#ifndef ENEMY_H
#define ENEMY_H

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
  string name = " ";
  bool boss = false;
  int health = 0;
  int level = 0;
  int rewardTier= 0;
  double meleeVulnerability = 1.0;
  double magicVulnerability = 1.0;
  double rangedVulnerability = 1.0;
  
protected:
  // Helper Functions
  void setEnemyLevel(int playerLevel);
  virtual void announceEnemy() const;

public:
  // Accessors
  virtual string getNickname() const { return name; }
  string getName() const { return name; }
  int getHealth() const { return health; }
  int getLevel() const { return level; }
  int getRewardTier() const { return rewardTier; }
  double getVulnerability(const string &battleMenuSelection) const;
  virtual int attack(int playerArmor, int playerMaxHealth);

  // Mutators
  void receive(int playerAttack);
};

#endif // ENEMY_H
