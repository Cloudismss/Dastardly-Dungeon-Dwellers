#ifndef CHARACTERLIST_H
#define CHARACTERLIST_H

#include <string>

#include "Character.h"

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
  const int xpRequiredPerLevel = 100;

public:
  CharacterList();
  ~CharacterList();

  // Append new character
  void appendRandomCharacter();
  void appendCharacter(const std::string &className);

  // Remove character
  bool removeCurrentCharacter();
  bool removeCharacter(const std::string &className);

  // Switch current character
  bool cycle(char direction = 'R', const std::string &context = "Switch");
  void select(const std::string &characterName);

private:
  // Class selector
  std::string classSelection();
  bool classSelectionConfirm(const std::string &className);

public:
  // Generic Class Accessors
  std::string getClassName() const { return current->character->getClassName(); }
  double getHealth() const { return current->character->getHealth(); }
  double getXp() const { return current->character->getXp(); }
  int getLevel() const { return current->character->getLevel(); }
  int getWeaponLevel(int skillType) const { return current->character->getWeaponLevel(skillType); }

  // Class Specific Accessors
  int getSkillUpgradeTier(int skillType) const { return current->character->getSkillUpgradeTier(skillType); }
  int getSkillLevel(int skillType) const { return current->character->getSkillLevel(skillType); }
  double getCritLevel() const { return current->character->getCritLevel(); }
  double getMaxHealth() const { return current->character->getMaxHealth(); }
  std::string getSkillName(int skillType) const { return current->character->getSkillName(skillType); }

  // Generic Class Mutators
  void adjustHealth(double healthAdjust) { current->character->adjustHealth(healthAdjust); }
  void addXp(int xpAdjust) { current->character->addXp(xpAdjust); }
  void addLevel() { current->character->addLevel(); }
  void upgradeWeapon(int skillType, const std::string &upgradeName) { current->character->upgradeWeapon(skillType, upgradeName); }

  // Class Specific Mutators
  void useSkill(int skillType) { current->character->useSkill(skillType); }
  void upgradeSkillName(int skillType) { current->character->upgradeSkillName(skillType); }
  void adjustMaxHealth(double maxHealthAdjust) { current->character->adjustMaxHealth(maxHealthAdjust); }
};

#endif // CHARACTERLIST_H
