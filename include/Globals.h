#ifndef DASTARDLY_DUNGEON_DWELLERS_GLOBALS_H
#define DASTARDLY_DUNGEON_DWELLERS_GLOBALS_H

// Globals
const double BASE_CRIT_CHANCE = 0.10;
const double BASE_MELEE_MISS_CHANCE = 0.15;
const double BASE_MAGIC_MISS_CHANCE = 0.20;
const double BASE_RANGED_MISS_CHANCE = 0.30;
const short unsigned int BASE_PLAYER_HEALTH = 100;
const short unsigned int BASE_PLAYER_MELEE_DAMAGE = 20;
const short unsigned int BASE_PLAYER_MAGIC_DAMAGE = 25;
const short unsigned int BASE_PLAYER_RANGED_DAMAGE = 30;
const short unsigned int BASE_ENEMY_DAMAGE = 0.2 * BASE_PLAYER_HEALTH;
const short unsigned int BASE_ENEMY_HEALTH = 0.3 * BASE_PLAYER_HEALTH;
const short unsigned int BASE_BOSS_HEALTH = 5 * BASE_PLAYER_HEALTH;
const short unsigned int BASE_BOSS_DAMAGE = 0.5 * BASE_PLAYER_HEALTH;
const short unsigned int SKILL_UPGRADE = 7;
const short unsigned int CHECKPOINT_1 = 5;
const short unsigned int CHECKPOINT_2 = 10;
const short unsigned int CHECKPOINT_3 = 15;

#endif // DASTARDLY_DUNGEON_DWELLERS_GLOBALS_H
