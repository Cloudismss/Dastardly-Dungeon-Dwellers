#ifndef MINOTAUR_H
#define MINOTAUR_H

#include "Enemy.h"

class Minotaur : public Enemy
{
private:
  const static inline std::string enemyName = "Minotaur";
  const static inline double meleeVulnerability = 1.4;
  const static inline double magicVulnerability = 1.3;
  const static inline double rangedVulnerability = 0.8;
  const static inline double vulnerabilities[] = { meleeVulnerability, magicVulnerability, rangedVulnerability };

public:
  Minotaur(int playerLevel);
};

#endif // MINOTAUR_H
