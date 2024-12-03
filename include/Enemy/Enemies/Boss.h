#ifndef DASTARDLY_DUNGEON_DWELLERS_BOSS_H
#define DASTARDLY_DUNGEON_DWELLERS_BOSS_H

#include <vector>

#include "Enemy.h"

class Boss : public Enemy
{
private:
  std::vector<string> bosses =
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
  void announceEnemy() override;

public:
  Boss(int playerLevel);
  string getNickname() const override;
  int attack(int playerArmor, int playerMaxHealth) override;
};

#endif // DASTARDLY_DUNGEON_DWELLERS_BOSS_H
