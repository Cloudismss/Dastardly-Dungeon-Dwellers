#include "Archer.h"

Archer::Archer()
{
  setClassName();
  readSkills();
  generateSkillNames();
  health = maxHealth;
}

void Archer::generateSkillNames()
{
  // Number of skill levels per skill
  const short unsigned int SIZE = 3;

  // Archer Skill Names
  const string archerMelee[] = {"Slice", "Sever", "Blade Dance"};
  const string archerMagic[] = {"Poison Bomb", "Intoxicate", "Pestilence"};
  const string archerRanged[] = {"Pierce", "Perforate", "Serpent Shot"};

  for (int i = 0; i != SIZE; ++i)
  {
    skillNames["Melee"][i] = archerMelee[i];
    skillNames["Magic"][i] = archerMagic[i];
    skillNames["Ranged"][i] = archerRanged[i];
  }
}
