#ifndef DASTARDLY_DUNGEON_DWELLERS_BARD_H
#define DASTARDLY_DUNGEON_DWELLERS_BARD_H

#include "Character.h"

class Bard : public Character
{
private:
  void setClassName() override { className = "Bard"; }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_BARD_H
