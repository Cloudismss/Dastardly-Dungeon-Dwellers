#ifndef GLOBALS_H
#define GLOBALS_H

// Globals
const double BASE_CRIT_CHANCE = 0.10;
const double BASE_MELEE_MISS_CHANCE = 0.15;
const double BASE_MAGIC_MISS_CHANCE = 0.20;
const double BASE_RANGED_MISS_CHANCE = 0.30;
const double BASE_ENEMY_MISS_CHANCE = 0.15;
const int BASE_PLAYER_HEALTH = 100;
const int BASE_PLAYER_MELEE_DAMAGE = 0;
const int BASE_PLAYER_MAGIC_DAMAGE = 0;
const int BASE_PLAYER_RANGED_DAMAGE = 5;
const int BASE_ENEMY_DAMAGE = 0.2 * BASE_PLAYER_HEALTH;
const int BASE_ENEMY_HEALTH = 0.3 * BASE_PLAYER_HEALTH;
const int BASE_BOSS_HEALTH = 5 * BASE_PLAYER_HEALTH;
const int BASE_BOSS_DAMAGE = 0.5 * BASE_PLAYER_HEALTH;
const int SKILL_UPGRADE = 7;
const int CHECKPOINT_1 = 5;
const int CHECKPOINT_2 = 10;
const int CHECKPOINT_3 = 15;

namespace skill
{
  enum skills
  {
    MELEE,
    MAGIC,
    RANGED
  };
}

enum exitCodes
{
  SUCCESS = 0,
  FAIL = -1,
};

#endif // GLOBALS_H
