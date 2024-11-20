#include "Warrior.h"

Warrior::Warrior()
{
  setClassName();
  readSkills();
  generateSkillNames();
  health = maxHealth;
}

void Warrior::generateSkillNames()
{
  // Number of skill levels per skill
  const short unsigned int SIZE = 3;

  // Warrior Skill Names
  const string warriorMelee[] = {"Slash", "Cleave", "Behemoth Strike"};
  const string warriorMagic[] = {"Shield Charge", "Vortex Slam", "Arcane Lunge"};
  const string warriorRanged[] = {"Rock Throw", "Shield Throw", "Javelin Toss"};

  for (int i = 0; i != SIZE; ++i)
  {
    skillNames["Melee"][i] = warriorMelee[i];
    skillNames["Magic"][i] = warriorMagic[i];
    skillNames["Ranged"][i] = warriorRanged[i];
  }
}
