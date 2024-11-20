#ifndef DASTARDLY_DUNGEON_DWELLERS_MAGE_H
#define DASTARDLY_DUNGEON_DWELLERS_MAGE_H

#include "Character.h"

class Mage : public Character
{
public:
  Mage();
  
private:
  void setClassName() { className = "Mage"; }
  void generateSkillNames();
};

#endif // DASTARDLY_DUNGEON_DWELLERS_MAGE_H
