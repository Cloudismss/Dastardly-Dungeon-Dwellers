#ifndef CHARACTER_H
#define CHARACTER_H

#include <array>
#include <set>
#include <string>
#include <unordered_map>

class Character
{
public:
  Character(const std::string &className, const std::unordered_map<int, std::array<std::string, 3>> skillNames);
  ~Character() { }

private:
  static inline std::set<std::string> availableCharacters = { "Warrior", "Mage", "Archer", "Bard" };

public:
  static std::string getRandomAvailableCharacter();
  static bool available() { return !availableCharacters.empty(); }
  static bool getAvailability(const std::string &className);
  static void checkoutCharacter(const std::string &className);

private:
  // Helper Functions
  void initSkills();
  void generateSkills(std::ofstream &defaultCharacterStats);

public:
  // Generic Class Accessors
  std::string getClassName() const { return className; }
  int getHealth() const { return health; }
  int getXp() const { return xp; }
  int getLevel() const { return level; }
  int getWeaponLevel(int skillType) const;

  // Class Specific Accessors
  int getMaxHealth() const { return maxHealth; }
  int getSkillUpgradeTier(int skillType) const;
  int getSkillLevel(int skillType) const;
  double getCritLevel() const { return critLevel; }
  std::string getSkillName(int skillType);

public:
  // Generic Class Mutators
  void adjustHealth(int healthAdjust) { health += healthAdjust; }
  void addXp(int xpAdjust);
  void addLevel();
  void upgradeWeapon(int skillType, const std::string &upgradeName);

  // Class Specific Mutators
  void useSkill(int skillType);
  void upgradeSkillName(int skillType);
  void adjustMaxHealth(int maxHealthAdjust) { maxHealth += maxHealthAdjust; }

protected:
  // Constants
  const std::string className;
  const std::unordered_map<int, std::array<std::string, 3>> skillNames;

  // Generic Class Variables
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
};

#endif // CHARACTER_H
