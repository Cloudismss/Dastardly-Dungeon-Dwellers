#ifndef DASTARDLY_DUNGEON_DWELLERS_CHARACTERS_H
#define DASTARDLY_DUNGEON_DWELLERS_CHARACTERS_H

#include <string>

#include "Skills.h"

using std::string;

class Characters
{
private:
  friend class Player;

  // Doubley Linked Circular List
  struct Node
  {
    string className;
    double health;
    short unsigned int meleeWeapon, magicWeapon, rangedWeapon;
    Skills *skills;
    Node *next;
    Node *previous;
  };
  Node *head;
  Node *current;

  // Class selector
  void classSelection();
  bool classSelectionConfirm();

public:
  Characters();
  ~Characters();

  // Append
  void append(const string &className);
  void cycle(char direction);

  // Mutators
  void setClassName(string className) { current->className = className; }
  void adjustHealth(double healthAdjust) { current->health += healthAdjust; }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_CHARACTERS_H
