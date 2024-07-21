#include "Enemy.h"

#include <iostream>
#include <vector>

#include "Globals.h"

using std::cerr;
using std::cout;

// Enemy Class Constructor
Enemy::Enemy(Player *player)
{
  // Generate tier for enemy
  setEnemyTier(player);

  // Generate enemy type
  setEnemyName(player);
  setEnemyVulnerabilities();

  // Calculates health of the enemy based off of base enemy health and enemy tier
  health = BASE_ENEMY_HEALTH * tier;
  
  announceEnemy();

  // ! TODO: Debug
  debugPrint();
}

void Enemy::setEnemyTier(Player *player)
{
  // Randomizer variable for tier
  int randomTier = 1 + (rand() % 100);

  // Variables for Tier chance
  int tier1 = 0, tier2 = 0, tier3 = 0, tier4 = 0, tier5 = 0;

  // The first 5 rooms can spawn enemies Tier 1-2
  if (player->getProgression() < CHECKPOINT_1)
  {
    if (randomTier <= 80)
      tier = 1;
    else
      tier = 2;
  }

  // The next 5 rooms can spawn enemies Tier 1-3
  else if (player->getProgression() < CHECKPOINT_2)
  {
    // Calculates a random tier for the enemy - 60% chance of Tier 1, 30% chance of Tier 2, 10% chance of Tier 3
    tier1 = 60, tier2 = tier1 + 30;
    if (randomTier <= tier1)
      tier = 1;
    else if (randomTier <= tier2)
      tier = 2;
    else
      tier = 3;
  }

  // The next 5 rooms can spawn enemies Tier 1-4
  else if (player->getProgression() < CHECKPOINT_3)
  {
    // Calculates a random tier for the enemy - 35% chance of Tier 1, 30% chance of Tier 2, 25% chance of Tier 3, 10% chance of Tier 4
    tier1 = 35, tier2 = tier1 + 30, tier3 = tier2 + 25;
    if (randomTier <= tier1)
      tier = 1;
    else if (randomTier <= tier2)
      tier = 2;
    else if (randomTier <= tier3)
      tier = 3;
    else
      tier = 4;
  }

  // The final rooms can spawn enemies Tier 2-5
  else
  {
    // Calculates a random tier for the enemy - 35% chance of Tier 2, 25% chance of Tier 3, 20% chance of Tier 4, 15% chance of Tier 5, 5% chance of BOSS
    tier2 = 35, tier3 = tier2 + 25, tier4 = tier3 + 20, tier5 = tier4 + 15;
    if (randomTier <= tier2)
      tier = 2;
    else if (randomTier <= tier3)
      tier = 3;
    else if (randomTier <= tier4)
      tier = 4;
    else if (randomTier <= tier5)
      tier = 5;
    else
      boss = true;
  }

  rewardTier = tier;

  if (boss)
  {
    rewardTier = 10;
  }
}

void Enemy::setEnemyName(Player *player)
{
  // TODO: Weighted implementation with vector
  std::vector<string> baddies = { };
  std::vector<string> stage1Baddies = {"Goblin", "Orc", "Skeleton", "Troll"};
  std::vector<string> stage2Baddies = {"Cyclops"};
  std::vector<string> stage3Baddies = {"Minotaur"};
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
    // ! TODO: Figure out how to copy entire vector
    if (player->getProgression() == CHECKPOINT_1)
    {
      baddies.push_back(stage1Baddies[0]);
      name = baddies[rand() % baddies.size()];
    }
    else if (player->getProgression() == CHECKPOINT_2)
    {
      baddies.push_back(stage2Baddies[0]);
      name = baddies[rand() % baddies.size()];
    }
    else if (player->getProgression() == CHECKPOINT_3)
    {
      baddies.push_back(stage3Baddies[0]);
      name = baddies[rand() % baddies.size()];
    }
  }
  else
  {
    name = bosses[rand() % bosses.size()];
  }
}

void Enemy::setEnemyVulnerabilities()
{
  if (name == "Goblin")
  {
    meleeVulnerability = 2.0;
    magicVulnerability = 1.0;
    rangedVulnerability = 1.0;
  }
  else if (name == "Orc")
  {
    meleeVulnerability = 1.0;
    magicVulnerability = 2.0;
    rangedVulnerability = 1.0;
  }
  else if (name == "Skeleton")
  {
    meleeVulnerability = 2.0;
    magicVulnerability = 1.0;
    rangedVulnerability = 0.5;
  }
  else if (name == "Troll")
  {
    meleeVulnerability = 2.0;
    magicVulnerability = 1.0;
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
    meleeVulnerability = 2.0;
    magicVulnerability = 1.0;
    rangedVulnerability = 0.5;
  }
}

// TODO varied dialogue implementation
void Enemy::announceEnemy()
{
  // Print enemy attributes
  if (!boss)
    cout << "A tier " << tier << " " << name << " is guarding this room!\n\n";
  else
    cout << "\nThe Earth trembles beneath you, a powerful foe is near...\n" << name << " has cornered you!\n\n";
}

void Enemy::debugPrint()
{
  cout << "Name: " << name << "\n"
       << "Tier: " << tier << "\n"
       << "Health: " << health << "\n"
       << "Weakness to melee: " << meleeVulnerability << "\n"
       << "Weakness to magic: " << magicVulnerability << "\n"
       << "Weakness to ranged: " << rangedVulnerability << "\n";
}

void Enemy::receive(Player *player, const string &battleMenuSelection, double playerAttack)
{
  health -= playerAttack * getResistance(player, battleMenuSelection);
  if (health < 0)
    health = 0;
}

// Pre-condition: called by battleController(), passed enemy variables
// Post-condition: returns a damage amount based on enemy attributes
double Enemy::attack(int playerArmor)
{ 
  double damage = 0;
  if (!boss)
  {
    damage = (BASE_ENEMY_DAMAGE * tier) + (attackLow + (rand() % ((attackHigh + 1) - attackLow)));
    if (tier > 3)
      damage *= 0.85f;
  }
  else
    damage = BOSS_DAMAGE_LOW + (rand() % (BOSS_DAMAGE_HIGH + 1 - BOSS_DAMAGE_LOW));

  damage -= playerArmor;

  // One-shot protection
  if (damage > 19)
    damage = 19;

  // Stops players from healing when stacking a bunch of armor
  if (damage < 0)
    damage = 0;

  cout << "\t" << name << " dealt " << static_cast<int>(damage) << " damage\n\n";
  return damage;
}

// Pre-condition: called by playerDamage(), passed damageValue, skill variables, enemy variables, and result of battleMenu()
// Post-condition: updates damageValue based on enemy stats
double Enemy::getResistance(Player *player, const string &battleMenuSelection)
{
  double *resistance = nullptr;

  if (battleMenuSelection == "Melee")
    resistance = &meleeVulnerability;
  else if (battleMenuSelection == "Magic")
    resistance = &magicVulnerability;
  else if (battleMenuSelection == "Ranged")
    resistance = &rangedVulnerability;

  if (*resistance < 1.0)
    cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " is disappointingly ineffective against " << name << "!\n\n";
  else if (*resistance > 1.0)
    cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " is incredibly effective against " << name << "!\n\n";

  return *resistance;
}