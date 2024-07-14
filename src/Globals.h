#ifndef DASTARDLY_DUNGEON_DWELLERS_GLOBALS_H
#define DASTARDLY_DUNGEON_DWELLERS_GLOBALS_H

// Map Constants - feel free to change - have to both be odd numbers or positioning will be weird
const int MAP_ROWS = 9;
const int MAP_COLUMNS = 9;

// Globals
const float BASE_CRIT_CHANCE = 0.10;
const int BASE_MELEE_DAMAGE = 2;
const int BASE_MAGIC_DAMAGE = 2;
const int BASE_RANGED_DAMAGE = 3;
const int BASE_ENEMY_DAMAGE = 2;
const int BASE_ENEMY_HEALTH = 5;
const int BOSS_HEALTH = 100;
const int BOSS_DAMAGE_LOW = 8;
const int BOSS_DAMAGE_HIGH = 16;
const int SKILL_UPGRADE = 7;

// Debug toggle - displays useful debug information in the console and gives resources / increased damage
bool debug = false; // Enter -37 at the main menu to enter debug mode

#endif //DASTARDLY_DUNGEON_DWELLERS_GLOBALS_H