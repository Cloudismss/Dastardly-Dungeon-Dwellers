#include "Enemy Damage.h"

// Pre-condition: called by battleController(), passed enemy variables
// Post-condition: returns a damage amount based on enemy attributes
float enemyDamage(int enemyTier, const string &enemyName, bool boss, int armorCount)
{
  float damage = 0;
  if (!boss)
  {
    damage = (BASE_ENEMY_DAMAGE * enemyTier) + (1 + (rand() % 3));
    if (enemyTier > 3)
    {
      damage *= 0.85f;
    }
  }
  else
  {
    damage = BOSS_DAMAGE_LOW + (rand() % (BOSS_DAMAGE_HIGH + 1 - BOSS_DAMAGE_LOW));
  }

  damage -= armorCount;

  // One-shot protection
  if (damage > 19)
  {
    damage = 19;
  }

  // Stops players from healing when stacking a bunch of armor
  if (damage < 0)
  {
    damage = 0;
  }

  cout << "\t" << enemyName << " dealt " << static_cast<int>(damage) << " damage\n\n";
  return damage;
}