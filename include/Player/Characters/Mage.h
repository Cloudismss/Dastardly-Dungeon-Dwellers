#ifndef DASTARDLY_DUNGEON_DWELLERS_MAGE_H
#define DASTARDLY_DUNGEON_DWELLERS_MAGE_H

#include "Character.h"

class Mage : public Character
{
private:
  void setClassName() override { className = "Mage"; }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_MAGE_H
