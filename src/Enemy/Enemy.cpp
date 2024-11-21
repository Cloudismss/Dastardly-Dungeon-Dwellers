#include "Enemy.h"

#include <iostream>
#include <vector>

#include "Globals.h"

#include "fmt/color.h"

using std::cout;

// Enemy Class Constructor
Enemy::Enemy(short unsigned int playerProgression)
{
  // Generate tier for enemy
  setEnemyTier(playerProgression);

  // Generate enemy type
  setEnemyName(playerProgression);
  setEnemyVulnerabilities();

  // Calculates health of the enemy based off of base enemy health and enemy tier
  health = BASE_ENEMY_HEALTH * tier;
  
  announceEnemy();
}

void Enemy::setEnemyTier(short unsigned int playerProgression)
{
  // Randomizer variable for tier
  short unsigned int randomTier = 1 + (rand() % 100);

  // Variables for Tier chance
  short unsigned int tier1 = 0, tier2 = 0, tier3 = 0, tier4 = 0, tier5 = 0;

  // The first 5 rooms can spawn enemies Tier 1-2
  if (playerProgression < CHECKPOINT_1)
  {
    if (randomTier <= 80)
      tier = 1;
    else
      tier = 2;
  }

  // The next 5 rooms can spawn enemies Tier 1-3
  else if (playerProgression < CHECKPOINT_2)
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
  else if (playerProgression < CHECKPOINT_3)
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
    {
      boss = true;
      tier = 10;
    }
  }

  rewardTier = tier;

  if (boss)
  {
    rewardTier = 10;
  }
}

void Enemy::setEnemyName(short unsigned int playerProgression)
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
    if (playerProgression == 0)
      baddies.insert(baddies.end(), stage1Baddies.begin(), stage1Baddies.end());
    else if (playerProgression == CHECKPOINT_1)
      baddies.insert(baddies.end(), stage2Baddies.begin(), stage2Baddies.end());
    else if (playerProgression == CHECKPOINT_2)
      baddies.insert(baddies.end(), stage3Baddies.begin(), stage3Baddies.end());
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
    cout << "A tier " << tier << " " << name << " is guarding this room!\n\n";
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
double Enemy::getVulnerability(const string &battleMenuSelection, const string &skillName)
{
  double *vulnerability = nullptr;

  if (battleMenuSelection == "Melee")
    vulnerability = &meleeVulnerability;
  else if (battleMenuSelection == "Magic")
    vulnerability = &magicVulnerability;
  else if (battleMenuSelection == "Ranged")
    vulnerability = &rangedVulnerability;

  if (*vulnerability < 1.0)
  {
    cout << "\t" << skillName << " is ";
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "not very effective");
    cout << " against " << name << "!\n";
  }
  else if (*vulnerability > 1.5)
  {
    cout << "\t" << skillName << " is ";
    fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "super effective");
    cout << " against " << name << "!\n";
  }

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
  short int damage = 0;
  short unsigned int attackLow;
  short unsigned int attackHigh;
  if (!boss)
  {
    damage = BASE_ENEMY_DAMAGE * tier;

    if (tier > 3)
      damage *= 0.85f;
    
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
  damage -= playerArmor;

  // One-shot protection
  if (damage > playerMaxHealth)
    damage = playerMaxHealth - 1;

  // Stops players from healing when stacking a bunch of armor
  if (damage < 0)
    damage = 0;

  cout << "\t" << name << " dealt " << damage << " damage\n\n";
  return damage;
}
