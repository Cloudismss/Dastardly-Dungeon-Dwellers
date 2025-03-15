#ifndef MAGE_H
#define MAGE_H

#include "Character.h"

class Mage : public Character
{
public:
  Mage();
  
private:
  void setClassName() { className = "Mage"; }
  void generateSkillNames();
};

#endif // MAGE_H
