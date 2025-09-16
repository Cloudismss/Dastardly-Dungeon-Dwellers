#ifndef ARCHER_H
#define ARCHER_H

#include <array>
#include <string>

#include "Globals.h"

#include "Character.h"

class Archer : public Character
{
public:
  Archer();

private:
  const static inline std::string characterName = "Archer";
  const static inline std::unordered_map<int, std::array<std::string, 3>> characterSkillNames = {
    { skill::MELEE, { "Slice", "Sever", "Blade Dance" } },
    { skill::MAGIC, { "Poison Bomb", "Intoxicate", "Pestilence" } },
    { skill::RANGED, { "Pierce", "Perforate", "Serpent Shot" } }
  };
};

#endif // ARCHER_H
