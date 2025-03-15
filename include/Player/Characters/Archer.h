#ifndef ARCHER_H
#define ARCHER_H

#include "Character.h"

class Archer : public Character
{
public:
  Archer();

private:
  void setClassName() { className = "Archer"; }
  void generateSkillNames();
};

#endif // ARCHER_H
