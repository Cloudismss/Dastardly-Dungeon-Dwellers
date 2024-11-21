#ifndef DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
#define DASTARDLY_DUNGEON_DWELLERS_ENEMY_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Enemy
{
public:
  // TODO: Generate child enemy similar to Character.h
  static Enemy *getEnemy();

public:
  Enemy(short unsigned int playerProgression);
  ~Enemy() { };

private:
  const vector<string> stage1Baddies = {"Goblin", "Orc", "Skeleton", "Troll"};
  const vector<string> stage2Baddies = {"Cyclops"};
  const vector<string> stage3Baddies = {"Minotaur"};

protected:
  string name;
  bool boss = false;
  short int health;
  short unsigned int tier;
  short unsigned int rewardTier;
  double meleeVulnerability = 1.0;
  double magicVulnerability = 1.0;
  double rangedVulnerability = 1.0;
  
  // Helper Functions
  void setEnemyTier(short unsigned int playerProgression);
  void setEnemyName(short unsigned int playerProgression);
  void setEnemyVulnerabilities();
  void announceEnemy();

public:
  // Accessors
  string getName() const { return name; }
  string getNickname() const;
  short int getHealth() const { return health; }
  short unsigned int getTier() const { return tier; }
  short unsigned int getRewardTier() const { return rewardTier; }
  double getVulnerability(const string &battleMenuSelection, const string &skillName);

  // Mutators
  void receive(short unsigned int playerAttack);
  short unsigned int attack(short unsigned int playerArmor, short unsigned int playerMaxHealth);

  // Debug
  void debugPrint();
};

#endif // DASTARDLY_DUNGEON_DWELLERS_ENEMY_H
