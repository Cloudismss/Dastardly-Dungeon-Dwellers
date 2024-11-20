#ifndef DASTARDLY_DUNGEON_DWELLERS_CHARACTER_LIST_H
#define DASTARDLY_DUNGEON_DWELLERS_CHARACTER_LIST_H

#include <set>
#include <string>

#include "Character.h"

using std::set;
using std::string;

class CharacterList
{
private:
  // Doubley Linked Circular List
  struct Node
  {
    Character *character;
    Node *next;
    Node *previous;
  };
  Node *head = nullptr;
  Node *current = nullptr;

private:
  short unsigned int xpRequiredPerLevel = 100;
  set<string> availableCharacters;

public:
  CharacterList();
  ~CharacterList();

  // Append new character
  void addRandomCharacter();
  void addSpecificCharacter(const string &className);

  // Remove character
  bool removeCurrentCharacter();
  bool removeSpecificCharacter(const string &className);

  // Switch current character
  bool cycle(char direction = 'R', const string &context = "Switch");
  void select(const string &characterName);

private:
  // Class selector
  string classSelection();
  bool classSelectionConfirm(const string &className);

public:
  // Generic Class Accessors
  string getClassName() { return current->character->getClassName(); }
  double getHealth() { return current->character->getHealth(); }
  double getXp() { return current->character->getXp(); }
  short unsigned int getLevel() { return current->character->getLevel(); }
  short unsigned int getWeaponLevel(const string &weaponType) { return current->character->getWeaponLevel(weaponType); }

  // Class Specific Accessors
  short unsigned int getSkillUpgradeTier(const string &skillType) { return current->character->getSkillUpgradeTier(skillType); }
  short unsigned int getSkillLevel(const string &skillType) { return current->character->getSkillLevel(skillType); }
  double getCritLevel() { return current->character->getCritLevel(); }
  double getMaxHealth() { return current->character->getMaxHealth(); }
  // Retrieves value from skillNames
  string getSkillName(const string &skillType) { return current->character->getSkillName(skillType); }

  // Generic Class Mutators
  void adjustHealth(double healthAdjust) { current->character->adjustHealth(healthAdjust); }
  void addXp(int xpAdjust) { current->character->addXp(xpAdjust); }
  void addLevel() { current->character->addLevel(); }
  void upgradeWeapon(const string &weaponType, const string &upgradeName) { current->character->upgradeWeapon(weaponType, upgradeName); }

  // Class Specific Mutators
  void useSkill(const string &skillType) { current->character->useSkill(skillType); }
  void upgradeSkillName(const string &skillType) { current->character->upgradeSkillName(skillType); }
  void adjustMaxHealth(double maxHealthAdjust) { current->character->adjustMaxHealth(maxHealthAdjust); }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_CHARACTER_LIST_H
