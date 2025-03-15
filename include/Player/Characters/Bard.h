#ifndef BARD_H
#define BARD_H

#include "Character.h"

class Bard : public Character
{
public:
  Bard();
  
private:
  void setClassName() { className = "Bard"; }
  void generateSkillNames();
};

#endif // BARD_H
