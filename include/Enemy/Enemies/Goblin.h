#ifndef GOBLIN_H
#define GOBLIN_H

#include "Enemy.h"

class Goblin : public Enemy
{
private:
  const static inline std::string enemyName = "Goblin";
  const static inline double meleeVulnerability = 1.3;
  const static inline double magicVulnerability = 1.0;
  const static inline double rangedVulnerability = 1.4;
  const static inline double vulnerabilities[] = { meleeVulnerability, magicVulnerability, rangedVulnerability };

public:
  Goblin(int playerLevel);
};

#endif // GOBLIN_H
