#ifndef WARRIOR_H
#define WARRIOR_H

#include <array>
#include <string>

#include "Globals.h"

#include "Character.h"

class Warrior : public Character
{
public:
  Warrior();

private:
  const static inline std::string characterName = "Warrior";
  const static inline std::unordered_map<int, std::array<std::string, 3>> characterSkillNames = {
    { skill::MELEE, { "Slash", "Cleave", "Behemoth Strike" } },
    { skill::MAGIC, { "Shield Charge", "Vortex Slam", "Arcane Lunge" } },
    { skill::RANGED, { "Rock Throw", "Shield Throw", "Javelin Toss" } }
  };
};

#endif // WARRIOR_H
