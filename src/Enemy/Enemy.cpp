#include "Enemy.h"

#include <iostream>
#include <vector>

#include "Enemy Spawner.h"
#include "Globals.h"

using std::cout;

// Enemy Class Constructor
Enemy::Enemy()
{
  // Generate level for enemy
  setEnemyLevel();

  // Generate enemy type
  setEnemyName();
  setEnemyVulnerabilities();

  // Calculates health of the enemy based off of base enemy health and enemy level
  short unsigned int levelBoost = 0;
  for (int i = 1; i < level; ++i)
    levelBoost += BASE_ENEMY_HEALTH * 0.5;
  health = BASE_ENEMY_HEALTH + levelBoost;
  
  announceEnemy();
}

void Enemy::setEnemyLevel()
{
  // Randomizer variable for level
  short unsigned int randomLevel = 1 + (rand() % 100);

  // Variables for Level chance
  short unsigned int level1 = 0, level2 = 0, level3 = 0, level4 = 0, level5 = 0;

  // The first 5 rooms can spawn enemies Level 1-2
  if (EnemySpawner::getProgression() < CHECKPOINT_1)
  {
    if (randomLevel <= 80)
      level = 1;
    else
      level = 2;
  }

  // The next 5 rooms can spawn enemies Level 1-3
  else if (EnemySpawner::getProgression() < CHECKPOINT_2)
  {
    // Calculates a random level for the enemy - 60% chance of Level 1, 30% chance of Level 2, 10% chance of Level 3
    level1 = 60, level2 = level1 + 30;
    if (randomLevel <= level1)
      level = 1;
    else if (randomLevel <= level2)
      level = 2;
    else
      level = 3;
  }

  // The next 5 rooms can spawn enemies Level 1-4
  else if (EnemySpawner::getProgression() < CHECKPOINT_3)
  {
    // Calculates a random level for the enemy - 35% chance of Level 1, 30% chance of Level 2, 25% chance of Level 3, 10% chance of Level 4
    level1 = 35, level2 = level1 + 30, level3 = level2 + 25;
    if (randomLevel <= level1)
      level = 1;
    else if (randomLevel <= level2)
      level = 2;
    else if (randomLevel <= level3)
      level = 3;
    else
      level = 4;
  }

  // The final rooms can spawn enemies Level 2-5
  else
  {
    // Calculates a random level for the enemy - 35% chance of Level 2, 25% chance of Level 3, 20% chance of Level 4, 15% chance of Level 5, 5% chance of BOSS
    level2 = 35, level3 = level2 + 25, level4 = level3 + 20, level5 = level4 + 15;
    if (randomLevel <= level2)
      level = 2;
    else if (randomLevel <= level3)
      level = 3;
    else if (randomLevel <= level4)
      level = 4;
    else if (randomLevel <= level5)
      level = 5;
    else
    {
      boss = true;
      level = 10;
    }
  }

  rewardTier = level;

  if (boss)
  {
    rewardTier = 10;
  }
}

void Enemy::setEnemyName()
{
  // TODO: Weighted implementation with vector
  static vector<string> baddies;
  baddies.reserve(6);

  std::vector<string> bosses =
  {
    "Voidshaper Nihilus",
    "Snarltooth the Feral",
    "Dreadlord Vorkar",
    "Soulstealer Malgrimor",
    "King Rattleclaw",
    "Ignatius the Infernal",
    "Dreadmaw the Bonecrusher",
    "Rotclaw the Pustulant",
    "Sludgeheart the Grotesque",
    "Drak'thar the Trollking"
  };

  if (!boss)
  {
    if (EnemySpawner::getProgression() == 0)
      baddies.insert(baddies.end(), EnemySpawner::getStage1Baddies().begin(), EnemySpawner::getStage1Baddies().end());
    else if (EnemySpawner::getProgression() == CHECKPOINT_1)
      baddies.insert(baddies.end(), EnemySpawner::getStage2Baddies().begin(), EnemySpawner::getStage2Baddies().end());
    else if (EnemySpawner::getProgression() == CHECKPOINT_2)
      baddies.insert(baddies.end(), EnemySpawner::getStage3Baddies().begin(), EnemySpawner::getStage3Baddies().end());
    name = baddies[rand() % baddies.size()];
  }
  else
    name = bosses[rand() % bosses.size()];
}

void Enemy::setEnemyVulnerabilities()
{
  if (name == "Goblin")
  {
    meleeVulnerability = 1.3;
    magicVulnerability = 1.0;
    rangedVulnerability = 1.4;
  }
  else if (name == "Orc")
  {
    meleeVulnerability = 0.7;
    magicVulnerability = 2.0;
    rangedVulnerability = 1.0;
  }
  else if (name == "Skeleton")
  {
    meleeVulnerability = 2.0;
    magicVulnerability = 1.2;
    rangedVulnerability = 0.5;
  }
  else if (name == "Troll")
  {
    meleeVulnerability = 1.3;
    magicVulnerability = 0.6;
    rangedVulnerability = 2.0;
  }
  else if (name == "Cyclops")
  {
    meleeVulnerability = 1.0;
    magicVulnerability = 1.0;
    rangedVulnerability = 1.0;
  }
  else if (name == "Minotaur")
  {
    meleeVulnerability = 1.4;
    magicVulnerability = 1.3;
    rangedVulnerability = 0.8;
  }
}

// TODO: varied dialogue implementation
void Enemy::announceEnemy()
{
  // Print enemy attributes
  if (!boss)
    cout << "A level " << level << " " << name << " is guarding this room!\n\n";
  else
    cout << "\nThe Earth trembles beneath you, a powerful foe is near...\n" << name << " has cornered you!\n\n";
}

string Enemy::getNickname() const
{
  if (!boss)
    return name;

  if (name == "Voidshaper Nihilus")
    return "Nihilus";
  else if (name == "Snarltooth the Feral")
    return "Snarltooth";
  else if (name == "Dreadlord Vorkar")
    return "Vorkar";
  else if (name == "Soulstealer Malgrimor")
    return "Malgrimor";
  else if (name == "King Rattleclaw")
    return "Rattleclaw";
  else if (name == "Ignatius the Infernal")
    return "Ignatius";
  else if (name == "Dreadmaw the Bonecrusher")
    return "Dreadmaw";
  else if (name == "Rotclaw the Pustulant")
    return "Rotclaw";
  else if (name == "Sludgeheart the Grotesque")
    return "Sludgeheart";
  else if (name == "Drak'thar the Trollking")
    return "Drak'thar";

  return "Error";
}

// Pre-condition: called by playerDamage(), passed damageValue, skill variables, enemy variables, and result of battleMenu()
// Post-condition: updates damageValue based on enemy stats
double Enemy::getVulnerability(const string &battleMenuSelection)
{
  double *vulnerability = nullptr;

  if (battleMenuSelection == "Melee")
    vulnerability = &meleeVulnerability;
  else if (battleMenuSelection == "Magic")
    vulnerability = &magicVulnerability;
  else if (battleMenuSelection == "Ranged")
    vulnerability = &rangedVulnerability;

  return *vulnerability;
}

void Enemy::receive(short unsigned int playerAttack)
{
  health -= playerAttack;
  if (health < 0)
    health = 0;
}

// Pre-condition: called by battleController(), passed enemy variables
// Post-condition: returns a damage amount based on enemy attributes
short unsigned int Enemy::attack(short unsigned int playerArmor, short unsigned int playerMaxHealth)
{ 
  if (1 + (rand() % 100) <= BASE_ENEMY_MISS_CHANCE * 100)
  {
    cout << "\t" << name << " missed!\n\n";
    return 0;
  }

  short int damage = 0;
  short int attackLow = 0;
  short int attackHigh = 0;
  if (!boss)
  {
    damage = BASE_ENEMY_DAMAGE;

    for (int i = 1; i < level; ++i)
      damage *= 1.3;

    if (level > 3)
      damage *= 0.85;
    
    attackLow = (-0.1 * playerMaxHealth) + (-0.1 * damage);
    attackHigh = (0.1 * playerMaxHealth) + (0.1 * damage);
  }
  else
  {
    damage = BASE_BOSS_DAMAGE;

    attackLow = (-0.1 * playerMaxHealth) + (-0.1 * BASE_BOSS_DAMAGE);
    attackHigh = (0.1 * playerMaxHealth) + (0.1 * BASE_BOSS_DAMAGE);
  }

  // Damage offset for fun variance
  damage += (attackLow + (rand() % ((attackHigh + 1) - attackLow)));

  // Flat damage reduction via armor
  short unsigned int playerArmorProtection = 0;
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

  cout << "\t" << name << " dealt " << damage << " damage\n\n";
  return damage;
}
