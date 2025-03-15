#ifndef CHARACTER_H
#define CHARACTER_H

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
  static bool available() { return !availableCharacters.empty(); }
  static bool getAvailableCharacter(const string &className);
  static void checkoutCharacter(const string &className);

protected:
  void setClassName();
  void generateSkillNames();

protected:
  // Generic Class Variables
  string className;
  int health;
  int xp = 0;
  int level = 1;
  int meleeWeapon = 1, magicWeapon = 1, rangedWeapon = 1;

  // Class Specific Variables
  int maxHealth = 0;
  int meleeCounter = 0, magicCounter = 0, rangedCounter = 0;
  int meleeUpgradeTier = 0, magicUpgradeTier = 0, rangedUpgradeTier = 0;
  int meleeLevel = 0, rangedLevel = 0, magicLevel = 0;
  int xpRequiredPerLevel = 100;
  double critLevel = 1.0;
  // Map of skill names with array for indicating skill level - key is ability type [ Melee, Magic, or Ranged ]
  unordered_map<string, string [3]> skillNames;

protected:
  // Skill Helper Functions
  void readSkills();
  void generateSkills(std::ofstream &defaultCharacterStats);

public:
  // Generic Class Accessors
  string getClassName() const { return className; }
  int getHealth() const { return health; }
  int getXp() const { return xp; }
  int getLevel() const { return level; }
  int getWeaponLevel(const string &weaponType) const;

  // Class Specific Accessors
  int getMaxHealth() const { return maxHealth; }
  int getSkillUpgradeTier(const string &skillType) const;
  int getSkillLevel(const string &skillType) const;
  double getCritLevel() const { return critLevel; }
  // Retrieves value from skillNames
  string getSkillName(const string &skillType);

  // Generic Class Mutators
  void adjustHealth(int healthAdjust) { health += healthAdjust; }
  void addXp(int xpAdjust);
  void addLevel();
  void upgradeWeapon(const string &weaponType, const string &upgradeName);

  // Class Specific Mutators
  void useSkill(const string &skillType);
  void upgradeSkillName(const string &skillType);
  void adjustMaxHealth(int maxHealthAdjust) { maxHealth += maxHealthAdjust; }
};

#endif // CHARACTER_H
