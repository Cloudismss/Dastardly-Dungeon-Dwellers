#ifndef DASTARDLY_DUNGEON_DWELLERS_WARRIOR_H
#define DASTARDLY_DUNGEON_DWELLERS_WARRIOR_H

#include "Character.h"

class Warrior : public Character
{
private:
  void setClassName() override { className = "Warrior"; }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_WARRIOR_H
