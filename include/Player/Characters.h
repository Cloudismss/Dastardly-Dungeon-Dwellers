#ifndef DASTARDLY_DUNGEON_DWELLERS_CHARACTERS_H
#define DASTARDLY_DUNGEON_DWELLERS_CHARACTERS_H

#include <set>
#include <string>

#include "Skills.h"

using std::set;
using std::string;

class Characters
{
private:
  // Doubley Linked Circular List
  struct Node
  {
    string className;
    double maxHealth, health;
    double xp;
    short unsigned int level;
    short unsigned int meleeWeapon, magicWeapon, rangedWeapon;
    Skills *skills;
    Node *next;
    Node *previous;
  };
  Node *head;
  Node *current;
  set<string> availableCharacters;

public:
  Characters();
  ~Characters();

  // Append new character
  void addCharacter();

  // Switch current character
  void cycle(char direction);
  void select(const string &characterName);

private:
  // Class selector
  void classSelection();
  bool classSelectionConfirm();

public:
  // Accessors
  string getClassName() { return current->className; }
  double getMaxHealth() { return current->maxHealth; }
  double getHealth() { return current->health; }
  double getXp() { return current->xp; }
  short unsigned int getLevel() { return current->level; }
  short unsigned int getWeaponLevel(const string &weaponType);

  // Mutators
  void setClassName(string className) { current->className = className; }
  void adjustHealth(double healthAdjust) { current->health += healthAdjust; }
  void adjustMaxHealth(double maxHealthAdjust) { current->maxHealth += maxHealthAdjust; }
  void addXp(int XpAdjust);
  void addLevel(int levelAdjust = 1) { current->level += levelAdjust; }
  void upgradeWeapon(const string &weaponType, const string &upgradeName);

  // Skills Accessors (Friend link)
  short unsigned int getSkillLevel(const string &skillType);
  short unsigned int getSkillUpgrade(const string &skillType);
  string getSkillName(const string &skillType);
  double getcritLevel() { return current->skills->critLevel; }

  // Skills Mutators (Friend link)
  void useSkill(const string &skillType);
  void upgradeSkillName(const string &skillType);
};

#endif // DASTARDLY_DUNGEON_DWELLERS_CHARACTERS_H
