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
  double meleeVulnerability;
  double magicVulnerability;
  double rangedVulnerability;

  // ! TODO: balance
  int attackLow = 2;
  int attackHigh = 5;
  
  // Helper Functions
  void setEnemyTier(int playerProgression);
  void setEnemyName(int playerProgression);
  void setEnemyVulnerabilities();
  void announceEnemy();

public:
  // Mutators
  void receive(const string &battleMenuSelection, const string &skillName, double playerAttack);
  double attack(int playerArmor);

  // Accessors
  string getName() const { return name; }
  double getHealth() const { return health; }
  double getVulnerability(const string &battleMenuSelection, const string &skillName);
  int getTier() const { return tier; }
  int getRewardTier() const { return rewardTier; }

  // Debug
  void debugPrint();
};

#endif //DASTARDLY_DUNGEON_DWELLERS_ENEMY_H