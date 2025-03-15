#include "Enemy.h"

#include <iostream>

#include "Globals.h"

Enemy::Enemy(int playerLevel, const std::string& name, const double vulnerability[], bool boss) :
  name(name),
  vulnerability(vulnerability[skill::MELEE], vulnerability[skill::MAGIC], vulnerability[skill::RANGED]),
  boss(boss),
  level(setLevel(playerLevel)),
  rewardTier(setRewardTier(playerLevel))
{
  // Calculates health of the enemy based off of base enemy health and enemy level
  int levelBoost = 0;
  for (int i = 1; i < level; ++i)
    levelBoost += BASE_ENEMY_HEALTH * 0.5;
  health = BASE_ENEMY_HEALTH + levelBoost;

  announceEnemy();
}

// TODO: add fun logic to allow lower AND higher level enemies
int setLevel(int playerLevel)
{
  int level = 1;
  int randomVariation = 1 + rand() % 100;

  // First room guarantees a level one enemy
  if (Enemy::getProgression() == 0)
    return level;

  // The first 5 rooms can only spawn enemies at player level
  else if (Enemy::getProgression() < CHECKPOINT_1)
    return playerLevel;
  
  // The next 5 rooms can spawn enemies up to 1 level higher than the player
  else if (Enemy::getProgression() < CHECKPOINT_2)
  {
    if (randomVariation < 50)
      return playerLevel;
    else
      return playerLevel + 1;
  }

  // The next 5 rooms can spawn enemies up to 2 levels higher than the player
  else if (Enemy::getProgression() < CHECKPOINT_3)
  {
    if (randomVariation < 10)
      return playerLevel;
    else if (randomVariation < 70)
      return playerLevel + 1;
    else
      return playerLevel + 2;
  }
  
  // The final rooms guarantee enemies spawn at least 1 level higher than the player
  else if (Enemy::getProgression() >= CHECKPOINT_3)
  {
    if (randomVariation < 25)
      return playerLevel + 1;
    else if (randomVariation < 75)
      return playerLevel + 2;
    else
      return playerLevel + 3;
  }

  // TODO: Prefer exception for end of control path
  return FAIL;
}

// TODO: Add depth
int Enemy::setRewardTier(int playerLevel)
{
  if (boss)
    return 10;

  return level;
}

// TODO: varied dialogue implementation
void Enemy::announceEnemy() const
{
  std::cout << "A level " << level << " " << name << " is guarding this room!\n\n";
}

int Enemy::attack(int playerArmor, int playerMaxHealth)
{ 
  if (1 + (rand() % 100) <= BASE_ENEMY_MISS_CHANCE * 100)
  {
    std::cout << "\t" << name << " missed!\n\n";
    return 0;
  }

  int damage = 0;
  int attackLow = 0;
  int attackHigh = 0;

  damage = BASE_ENEMY_DAMAGE;

  for (int i = 1; i < level; ++i)
    damage *= 1.3;

  if (level > 3)
    damage *= 0.85;
  
  attackLow = (-0.1 * playerMaxHealth) + (-0.1 * damage);
  attackHigh = (0.1 * playerMaxHealth) + (0.1 * damage);

  // Damage offset for fun variance
  damage += (attackLow + (rand() % ((attackHigh + 1) - attackLow)));

  // Flat damage reduction via armor
  int playerArmorProtection = 0;
  double percentBlocked = 1.0;
  for (int i = 0; i < playerArmor; ++i)
  {
    if (playerArmor == 1)
      playerArmorProtection = 1; // So we don't multiply by 0 below
    percentBlocked += 5;
  }
  playerArmorProtection *= percentBlocked;
  damage -= playerArmorProtection;

  // Player one-shot protection
  if (damage > playerMaxHealth)
    damage = playerMaxHealth - 1;

  // Stops players from healing when stacking a bunch of armor
  if (damage < 0)
    damage = 0;

  std::cout << "\t" << name << " dealt " << damage << " damage\n\n";
  return damage;
}

void Enemy::receive(int playerAttack)
{
  health -= playerAttack;
  if (health < 0)
    health = 0;
}
