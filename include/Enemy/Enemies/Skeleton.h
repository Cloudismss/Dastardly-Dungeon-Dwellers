#ifndef SKELETON_H
#define SKELETON_H

#include "Enemy.h"

class Skeleton : public Enemy
{
public:
  Skeleton(int playerLevel);

private:
  const static inline std::string enemyName = "Skeleton";
  const static inline double meleeVulnerability = 2.0;
  const static inline double magicVulnerability = 1.2;
  const static inline double rangedVulnerability = 0.5;
  const static inline double vulnerabilities[] = { meleeVulnerability, magicVulnerability, rangedVulnerability };
};

#endif // SKELETON_H
