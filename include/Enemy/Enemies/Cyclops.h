#ifndef CYCLOPS_H
#define CYCLOPS_H

#include "Enemy.h"

class Cyclops : public Enemy
{
public:
  Cyclops(int playerLevel);

private:
  const static inline std::string enemyName = "Cyclops";
  const static inline double meleeVulnerability = 1.0;
  const static inline double magicVulnerability = 1.0;
  const static inline double rangedVulnerability = 1.0;
  const static inline double vulnerabilities[] = { meleeVulnerability, magicVulnerability, rangedVulnerability };
};

#endif // CYCLOPS_H
