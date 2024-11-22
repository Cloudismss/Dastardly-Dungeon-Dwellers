#ifndef DASTARDLY_DUNGEON_DWELLERS_CHARACTER_H
#define DASTARDLY_DUNGEON_DWELLERS_CHARACTER_H

#include <set>
#include <string>
#include <unordered_map>

using std::set;
using std::string;
using std::unordered_map;

class Character
{
public:
  Character() { }
  ~Character() { }

private:
  inline static set<string> availableCharacters = { "Warrior", "Mage", "Archer", "Bard" };
public:
  static string getRandomAvailableCharacter();
  static bool getAvailableCharacter(const string &className);
  static void checkoutCharacter(const string &className);

protected:
  void setClassName();
  void generateSkillNames();

protected:
  // Generic Class Variables
  string className;
  short int health;
  short unsigned int xp = 0;
  short unsigned int level = 1;
  short unsigned int meleeWeapon = 1, magicWeapon = 1, rangedWeapon = 1;

  // Class Specific Variables
  short unsigned int maxHealth = 0;
  short unsigned int meleeCounter = 0, magicCounter = 0, rangedCounter = 0;
  short unsigned int meleeUpgradeTier = 0, magicUpgradeTier = 0, rangedUpgradeTier = 0;
  short unsigned int meleeLevel = 0, rangedLevel = 0, magicLevel = 0;
  short unsigned int xpRequiredPerLevel = 100;
  double critLevel = 1.0;
  // Map of skill names with array for indicating skill level - key is ability type [ Melee, Magic, or Ranged ]
  unordered_map<string, string [3]> skillNames;

protected:
  // Skill Helper Functions
  void readSkills();
  void generateSkills(std::ofstream &defaultCharacterStats);

public:
  // Generic Class Accessors
  string getClassName() { return className; }
  short int getHealth() { return health; }
  short unsigned int getXp() { return xp; }
  short unsigned int getLevel() { return level; }
  short unsigned int getWeaponLevel(const string &weaponType);

  // Class Specific Accessors
  short unsigned int getMaxHealth() { return maxHealth; }
  short unsigned int getSkillUpgradeTier(const string &skillType);
  short unsigned int getSkillLevel(const string &skillType);
  double getCritLevel() { return critLevel; }
  // Retrieves value from skillNames
  string getSkillName(const string &skillType);

  // Generic Class Mutators
  void adjustHealth(short int healthAdjust) { health += healthAdjust; }
  void addXp(short unsigned int xpAdjust);
  void addLevel();
  void upgradeWeapon(const string &weaponType, const string &upgradeName);

  // Class Specific Mutators
  void useSkill(const string &skillType);
  void upgradeSkillName(const string &skillType);
  void adjustMaxHealth(short unsigned int maxHealthAdjust) { maxHealth += maxHealthAdjust; }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_CHARACTER_H
