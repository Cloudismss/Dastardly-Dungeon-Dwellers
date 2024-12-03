#include "Mage.h"

Mage::Mage()
{
  setClassName();
  readSkills();
  generateSkillNames();
  health = maxHealth;
}

void Mage::generateSkillNames()
{
  // Number of skill levels per skill
  const int SIZE = 3;

  // Mage Skill Names
  const string mageMelee[] = {"Bonk", "Whack", "Astral Thump"};
  const string mageMagic[] = {"Frost Blast", "Arctic Veil", "Flash Freeze"};
  const string mageRanged[] = {"Zap", "Thunderbolt", "Thunderstorm"};

  for (int i = 0; i != SIZE; ++i)
  {
    skillNames["Melee"][i] = mageMelee[i];
    skillNames["Magic"][i] = mageMagic[i];
    skillNames["Ranged"][i] = mageRanged[i];
  }
}
