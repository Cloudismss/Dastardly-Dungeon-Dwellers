#include "Enemy.h"

// Enemy Class Definitions
Enemy::Enemy()
{
  name = generateEnemy();
}

void Enemy::setEnemyAttributes()
{
  std::cerr << "Error: This text should be overwritten\n";
}

// ! TEMP
void Enemy::tempEnemySpawner(Player *player)
{
// Randomizer variable for tier
  int randomTier = 1 + (rand() % 100);

  // Variables for Tier chance
  int tier1 = 0, tier2 = 0, tier3 = 0, tier4 = 0, tier5 = 0;

  // The first 5 rooms can spawn enemies Tier 1-2
  if (player->getProgression() < 5)
  {
    if (randomTier <= 80)
      tier = 1;
    else
      tier = 2;
  }

  // The next 5 rooms can spawn enemies Tier 1-3
  else if (player->getProgression() < 10)
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
  else if (player->getProgression() < 15)
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

  // Establish non-boss enemy values
  if (!boss)
  {
    // Calculates health of the enemy based off of base enemy health and enemy tier
    health = BASE_ENEMY_HEALTH * tier;

    // Assigns a random name to the enemy
    int randomName = 0;
    int randomValue = 1 + (rand() % 100);
    if (player->getProgression() < 5)
    {
      // 90% chance of enemies 1 - 2
      if (randomValue <= 90)
        randomName = 1 + (rand() % 2);
      // 10% chance of enemy 3
      else
        randomName = 3;
    }
    if (player->getProgression() < 10)
    {
      // 70% chance of enemies 1 - 2
      if (randomValue <= 70)
        randomName = 1 + (rand() % 2);
      // 30% chance of enemy 3
      else
        randomName = 3;
    }
    else if (player->getProgression() < 15)
    {
      // 70% chance of enemies 1, 2, 4, or 5
      if (randomValue < 70)
      {
        bool goodValue = false;
        int randomValueAgain = 0;
        do
        {
          randomValueAgain = rand() % 4;
          if (randomValueAgain != 1)
            goodValue = true;
        } while (!goodValue);
        randomName = 1 + (rand() % 2) + randomValueAgain;
      }
      // 30% chance of enemy 3
      else
        randomName = 3;
    }
    else
    {
      // 40% chance of enemies 1 - 4
      if (randomValue <= 40)
        randomName = 1 + (rand() % 4);
      // 60% chance of enemies 4 - 6
      else
        randomName = 4 + (rand() % 3);
    }

    switch (randomName)
    {
      case 1:
      {
        name = "Goblin"; // Weak to Melee, Neutral to Ranged, Neutral to Melee
        break;
      }
      case 2:
      {
        name = "Orc"; // Weak to Magic, Neutral to Ranged, Neutral to Melee
        break;
      }
      case 3:
      {
        name = "Troll"; // Weak to Ranged and Melee, Neutral to Magic
        health *= 2;
        break;
      }
      case 4:
      {
        name = "Skeleton"; // Weak to Melee, Neutral to Magic, Resistant to Ranged
        break;
      }
      case 5:
      {
        name = "Cyclops"; // Neutral to Melee, Neutral to Magic, Neutral to Ranged
        break;
      }
      case 6:
      {
        name = "Minotaur"; // Weak to Ranged and Magic, Resistant to Melee
        health *= 2;
        break;
      }
    }

    // Print enemy attributes
    cout << "A tier " << tier << " " << name << " is guarding this room!\n\n";
    rewardTier = tier; // Reward tier is used to control loot drops
  }

  // Establish enemy values as boss values
  else
  {
    // Boss health
    health = BOSS_HEALTH;
    rewardTier = 10; // This value is only used to control loot drops
    int randomBossName = 1 + (rand() % 10);

    // Assigns a random boss name
    switch (randomBossName)
    {
      case 1:
      {
        name = "Voidshaper Nihilus";
        break;
      }
      case 2:
      {
        name = "Snarltooth the Feral";
        break;
      }
      case 3:
      {
        name = "Dreadlord Vorkar";
        break;
      }
      case 4:
      {
        name = "Soulstealer Malgrimor";
        break;
      }
      case 5:
      {
        name = "King Rattleclaw";
        break;
      }
      case 6:
      {
        name = "Ignatius the Infernal";
        break;
      }
      case 7:
      {
        name = "Dreadmaw the Bonecrusher";
        break;
      }
      case 8:
      {
        name = "Rotclaw the Pustulant";
        break;
      }
      case 9:
      {
        name = "Sludgeheart the Grotesque";
        break;
      }
      case 10:
      {
        name = "Drak'thar the Trollking";
        break;
      }
    }

    // Some cool boss spawning text
    cout << "\nThe Earth trembles beneath you, a powerful foe is near...\n"
         << name << " has cornered you!\n\n";
  }  
}

string Enemy::generateEnemy()
{
  // TODO: Weighted implementation with vector
  std::vector<string> stage1Baddies = {"Goblin", "Orc", "Skeleton", "Troll"};
  std::vector<string> stage2Baddies = {"Cyclops"};
  std::vector<string> stage3Baddies = {"Minotaur"};
  return stage1Baddies[1 + (rand() % stage1Baddies.size())];
}

void Enemy::receive(double healthAdjust, const string &attackType)
{
  // TODO: Needs class based implementation of resistance
  double resistance = 0;
  if (attackType == "Melee")
    resistance = meleeVulnerability;
  else if (attackType == "Magic")
    resistance = magicVulnerability;
  else if (attackType == "Ranged")
    resistance = rangedVulnerability;
  health -= healthAdjust * resistance;
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
  double resistanceValue = 1.00;

  if (!boss)
  {
    if (name == "Goblin")
    {
      // Goblin is weak to Melee, but neutral to the rest
      if (battleMenuSelection == "Melee")
      {
        resistanceValue = 2.0;
        cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " is incredibly effective against " << name << "!\n\n";
      }
      else
        resistanceValue = 1.0;
    }
    else if (name == "Orc")
    {
      // Orc is weak to Magic, Neutral to the rest
      if (battleMenuSelection == "Magic")
      {
        resistanceValue = 2.0;
        cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " is incredibly effective against " << name << "!\n\n";
      }
      else
        resistanceValue = 1.0;
    }
    else if (name == "Troll")
    {
      // Troll is weak to Ranged and Melee, Neutral to Magic
      if (battleMenuSelection == "Melee")
      {
        resistanceValue = 2.0;
        cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " is incredibly effective against " << name << "!\n\n";
      }
      if (battleMenuSelection == "Ranged")
      {
        resistanceValue = 2.0;
        cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " is incredibly effective against " << name << "!\n\n";
      }
      else
        resistanceValue = 1.0;
    }
    else if (name == "Skeleton")
    {
      // Skeleton is weak to Melee, Neutral to Magic, and Resistant to Ranged
      if (battleMenuSelection == "Melee")
      {
        resistanceValue = 2.0;
        cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " is incredibly effective against " << name << "!\n\n";
      }
      if (battleMenuSelection == "Magic")
        resistanceValue = 1.0;
      if (battleMenuSelection == "Ranged")
      {
        resistanceValue = 0.5;
        cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " is disappointingly ineffective against " << name << "\n\n";
      }
    }
    else if (name == "Cyclops")
    {
      resistanceValue = 1.0;
    }
    else if (name == "Minotaur")
    {
      if (battleMenuSelection == "Melee")
      {
        // Minotaur is weak to Ranged and Magic, Resistant to Melee
        resistanceValue = 0.5;
        cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " is disappointingly ineffective against " << name << "\n\n";
      }
      else if (battleMenuSelection == "Magic")
      {
        resistanceValue = 2.0;
        cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " is incredibly effective against " << name << "!\n\n";
      }
      else if (battleMenuSelection == "Ranged")
      {
        resistanceValue = 2.0;
        cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " is incredibly effective against " << name << "!\n\n";
      }
    }
  }

  // Players deal triple damage vs. bosses
  else
    resistanceValue = 3.0;

  return resistanceValue;
}

// TODO varied dialogue implementation
void Enemy::announceEnemy()
{
  std::cout << "Yikes! A tier " << tier << " " << name << " has appeared {PLACEHOLDER}\n";
}

void Enemy::debugPrint()
{
  cout << "Name: " << name << "\n"
       << "Tier: " << tier << "\n"
       << "Health: " << health << "\n"
       << "Damage: " << damage << "\n"
       << "Weakness to melee: " << meleeVulnerability << "\n"
       << "Weakness to magic: " << magicVulnerability << "\n"
       << "Weakness to ranged: " << rangedVulnerability << "\n"
       << "Attack range: " << attackLow << "-" << attackHigh << "\n";
}