#ifndef BARD_H
#define BARD_H

#include <array>
#include <string>

#include "Globals.h"

#include "Character.h"

class Bard : public Character
{
public:
  Bard();

private:
  const static inline std::string characterName = "Bard";
  const static inline std::unordered_map<int, std::array<std::string, 3>> characterSkillNames = {
    { skill::MELEE, { "Slap", "Snuggle", "Strum" } },
    { skill::MAGIC, { "Beg", "Sing", "Serenade" } },
    { skill::RANGED, { "Waft", "Whistle", "Seduce" } }
  };
};

#endif // BARD_H
