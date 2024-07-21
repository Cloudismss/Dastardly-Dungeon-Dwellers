#ifndef DASTARDLY_DUNGEON_DWELLERS_BOSS_H
#define DASTARDLY_DUNGEON_DWELLERS_BOSS_H

#include <string>
#include <vector>

#include "Enemy.h"

using std::string;

class Boss: public Enemy
{
public:
  void setEnemyAttributes() override;

private:
  std::vector<string> Bosses 
  {
    "Voidshaper Nihilus",
    "Snarltooth the Feral",
    "Dreadlord Vorkar",
    "Soulstealer Malgrimor",
    "King Rattleclaw",
    "Ignatius the Infernal",
    "Dreadmaw the Bonecrusher",
    "Rotclaw the Pustulant",
    "Sludgeheart the Grotesque",
    "Drak'thar the Trollking"
  };
};

#endif //DASTARDLY_DUNGEON_DWELLERS_BOSS_H