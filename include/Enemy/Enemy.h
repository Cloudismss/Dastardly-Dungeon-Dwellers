#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_H

#include <string>

using std::string;

class Enemy
{
public:
  Enemy(int playerProgression);
  ~Enemy() { };

protected:
  string name;
  bool boss = false;
  int tier;
  int rewardTier;
  double health;
  double meleeVulnerability = 1.0;
  double magicVulnerability = 1.0;
  double rangedVulnerability = 1.0;

  // ! TODO: balance
  int attackLow = 2;
  int attackHigh = 5;
  
  // Helper Functions
  void setEnemyTier(int playerProgression);
  void setEnemyName(int playerProgression);
  void setEnemyVulnerabilities();
  void announceEnemy();

public:
  // Accessors
  string getName() const { return name; }
  double getHealth() const { return health; }
  double getVulnerability(const string &battleMenuSelection, const string &skillName);
  int getTier() const { return tier; }
  int getRewardTier() const { return rewardTier; }

  // Mutators
  void receive(double playerAttack);
  double attack(int playerArmor, double playerMaxHealth);

  // Debug
  void debugPrint();
};

#endif // DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
