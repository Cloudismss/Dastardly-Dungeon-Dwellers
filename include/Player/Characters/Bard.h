#ifndef DASTARDLY_DUNGEON_DWELLERS_BARD_H
#define DASTARDLY_DUNGEON_DWELLERS_BARD_H

#include "Character.h"

class Bard : public Character
{
public:
  Bard();
  
private:
  void setClassName() { className = "Bard"; }
  void generateSkillNames();
};

#endif // DASTARDLY_DUNGEON_DWELLERS_BARD_H
