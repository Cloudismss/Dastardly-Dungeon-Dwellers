#ifndef ORC_H
#define ORC_H

#include "Enemy.h"

class Orc : public Enemy
{
public:
  Orc(int playerLevel);

private:
  const static inline std::string enemyName = "Orc";
  const static inline double meleeVulnerability = 0.7;
  const static inline double magicVulnerability = 2.0;
  const static inline double rangedVulnerability = 1.0;
  const static inline double vulnerabilities[] = { meleeVulnerability, magicVulnerability, rangedVulnerability };
};

#endif // ORC_H
