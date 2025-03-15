#ifndef CHARACTERLIST_H
#define CHARACTERLIST_H

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
  int xpRequiredPerLevel = 100;

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
  string getClassName() const { return current->character->getClassName(); }
  double getHealth() const { return current->character->getHealth(); }
  double getXp() const { return current->character->getXp(); }
  int getLevel() const { return current->character->getLevel(); }
  int getWeaponLevel(int skillType) const { return current->character->getWeaponLevel(skillType); }

  // Class Specific Accessors
  int getSkillUpgradeTier(int skillType) const { return current->character->getSkillUpgradeTier(skillType); }
  int getSkillLevel(int skillType) const { return current->character->getSkillLevel(skillType); }
  double getCritLevel() const { return current->character->getCritLevel(); }
  double getMaxHealth() const { return current->character->getMaxHealth(); }
  // Retrieves value from skillNames
  string getSkillName(int skillType) const { return current->character->getSkillName(skillType); }

  // Generic Class Mutators
  void adjustHealth(double healthAdjust) { current->character->adjustHealth(healthAdjust); }
  void addXp(int xpAdjust) { current->character->addXp(xpAdjust); }
  void addLevel() { current->character->addLevel(); }
  void upgradeWeapon(int skillType, const string &upgradeName) { current->character->upgradeWeapon(skillType, upgradeName); }

  // Class Specific Mutators
  void useSkill(int skillType) { current->character->useSkill(skillType); }
  void upgradeSkillName(int skillType) { current->character->upgradeSkillName(skillType); }
  void adjustMaxHealth(double maxHealthAdjust) { current->character->adjustMaxHealth(maxHealthAdjust); }
};

#endif // CHARACTERLIST_H
