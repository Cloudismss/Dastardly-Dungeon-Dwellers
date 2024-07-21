/*
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
      // Boss health
    health = BOSS_HEALTH;
    rewardTier = 10; // This value is only used to control loot drops
    // Some cool boss spawning text
    cout << "\nThe Earth trembles beneath you, a powerful foe is near...\n"
         << name << " has cornered you!\n\n";
};

#endif //DASTARDLY_DUNGEON_DWELLERS_BOSS_H
*/