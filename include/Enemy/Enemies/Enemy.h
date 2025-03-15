#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy
{
public:
  Enemy(int playerLevel, const std::string& name, bool boss, const double vulnerability[]);
  ~Enemy() { ++enemyProgression; }

private:
  static inline int enemyProgression = 0;

public:
  static int getProgression() { return enemyProgression; }
  
private:
  int setLevel(int playerLevel);
  int setRewardTier(int playerLevel);

protected:
  virtual void announceEnemy() const = 0;

public:
  // Virtual Accessors
  virtual std::string getNickname() const { return name; }
  virtual int attack(int playerArmor, int playerMaxHealth);

public:
  // Accessors
  std::string getName() const { return name; }
  int getHealth() const { return health; }
  int getLevel() const { return level; }
  int getRewardTier() const { return rewardTier; }
  double getVulnerability(int battleSelection) const { return vulnerability[battleSelection]; }

public:
  // Mutators
  void receive(int playerAttack);

protected:
  const std::string name;
  const bool boss;
  const int level;
  const int rewardTier;
  const double vulnerability[3];

protected:
  int health = 20;
};

#endif // ENEMY_H
