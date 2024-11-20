#include "Bard.h"

void Character::generateSkillNames()
{
  // Number of skill levels per skill
  const short unsigned int SIZE = 3;

  // Bard Skill Names
  const string bardMelee[] = {"Slap", "Snuggle", "Strum"};
  const string bardMagic[] = {"Beg", "Sing", "Serenade"};
  const string bardRanged[] = {"Waft", "Whistle", "Seduce"};

  for (int i = 0; i != SIZE; ++i)
  {
    skillNames["Melee"][i] = bardMelee[i];
    skillNames["Magic"][i] = bardMagic[i];
    skillNames["Ranged"][i] = bardRanged[i];
  }
}