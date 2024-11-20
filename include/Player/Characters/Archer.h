#ifndef DASTARDLY_DUNGEON_DWELLERS_ARCHER_H
#define DASTARDLY_DUNGEON_DWELLERS_ARCHER_H

#include "Character.h"

class Archer : public Character
{
public:
  Archer();

private:
  void setClassName() { className = "Archer"; }
  void generateSkillNames();
};

#endif // DASTARDLY_DUNGEON_DWELLERS_ARCHER_H
