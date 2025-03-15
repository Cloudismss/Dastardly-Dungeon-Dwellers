#ifndef TROLL_H
#define TROLL_H

#include "Enemy.h"

class Troll : public Enemy
{
public:
  Troll(int playerLevel);

private:
  const static inline std::string enemyName = "Troll";
  const static inline double meleeVulnerability = 1.3;
  const static inline double magicVulnerability = 0.6;
  const static inline double rangedVulnerability = 2.0;
  const static inline double vulnerabilities[] = { meleeVulnerability, magicVulnerability, rangedVulnerability };
};

#endif // TROLL_H
