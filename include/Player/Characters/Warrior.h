#ifndef DASTARDLY_DUNGEON_DWELLERS_WARRIOR_H
#define DASTARDLY_DUNGEON_DWELLERS_WARRIOR_H

#include "Character.h"

class Warrior : public Character
{
public:
  Warrior();
  
private:
  void setClassName() { className = "Warrior"; }
  void generateSkillNames();
};

#endif // DASTARDLY_DUNGEON_DWELLERS_WARRIOR_H
