#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

class Warrior : public Character
{
public:
  Warrior();
  
private:
  void setClassName() { className = "Warrior"; }
  void generateSkillNames();
};

#endif // WARRIOR_H
