#ifndef DASTARDLY_DUNGEON_DWELLERS_ARCHER_H
#define DASTARDLY_DUNGEON_DWELLERS_ARCHER_H

#include "Character.h"

class Archer : public Character
{
private:
  void setClassName() override { className = "Archer"; }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_ARCHER_H
