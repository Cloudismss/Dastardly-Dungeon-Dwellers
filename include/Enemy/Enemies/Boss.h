#ifndef BOSS_H
#define BOSS_H

#include <string>
#include <vector>

#include "Enemy.h"

class Boss : public Enemy
{
public:
  Boss(int playerLevel);

private:
  // Helper functions
  bool createBoss() override;
  void announceEnemy() const override;

public:
  // Accessors
  std::string getNickname() const override;

public:
  // Mutators
  int attack(int playerArmor, int playerMaxHealth) override;

private:
  const static inline std::vector<std::string> bosses = { "Voidshaper Nihilus",        "Snarltooth the Feral",
                                                          "Dreadlord Vorkar",          "Soulstealer Malgrimor",
                                                          "King Rattleclaw",           "Ignatius the Infernal",
                                                          "Dreadmaw the Bonecrusher",  "Rotclaw the Pustulant",
                                                          "Sludgeheart the Grotesque", "Drak'thar the Trollking" };
  const static inline double meleeVulnerability = 1.0;
  const static inline double magicVulnerability = 1.0;
  const static inline double rangedVulnerability = 1.0;
  const static inline double vulnerabilities[] = { meleeVulnerability, magicVulnerability, rangedVulnerability };
};

#endif // BOSS_H
