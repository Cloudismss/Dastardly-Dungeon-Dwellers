#include "Globals.h"
#include "Art.h"

// battleController group, these functions handle all battle related functions. Called within roomController group
int battleController(const string &className, int &rewardTier, int &potionCount, int armorCount, int enemyProgression, std::ifstream &characterStats);
int battleMenu(string &meleeName, string &magicName, string &rangedName, int playerHealth, int enemyHealth);
void battleHealthArt(int playerHealth, int enemyHealth);
void battleEnemySpawner(int &enemyTier, int &rewardTier, int &enemyHealth, string &enemyName, int enemyProgression, bool &boss);
float playerDamage(int battleMenuSelection, string &meleeName, string &magicName, string &rangedName, const string &className, const string &enemyName, bool boss, std::ifstream &characterStats);
float enemyResistance(const string &abilityName, const string &enemyName, bool boss, int battleMenuSelection);
float enemyDamage(int enemyTier, const string &enemyName, bool boss, int armorCount);
void skillNames(string &skillName, const string &skillType, string &upgradeMessage, const string &className, int tier = 1);
int weaponUpgrade (int checkWeaponUpgrade, int = -1);
int heal(int &potionCount);