#ifndef MAGE_H
#define MAGE_H

#include <array>
#include <string>

#include "Globals.h"

#include "Character.h"

class Mage : public Character
{
public:
  Mage();

private:
  const static inline std::string characterName = "Mage";
  const static inline std::unordered_map<int, std::array<std::string, 3>> characterSkillNames = {
    { skill::MELEE, { "Bonk", "Whack", "Astral Thump" } },
    { skill::MAGIC, { "Frost Blast", "Arctic Veil", "Flash Freeze" } },
    { skill::RANGED, { "Zap", "Thunderbolt", "Thunderstorm" } }
  };
};

#endif // MAGE_H
