#include "Enemy Spawner.h"

// Pre-condition: called by battleController(), passed enemy variables
// Post-condition: updates all enemy variables based on enemyProgression
void battleEnemySpawner(int &enemyTier, int &rewardTier, int &enemyHealth, string &enemyName, int enemyProgression, bool &boss)
{
  // Randomizer variable for enemyTier
  int randomTier = 1 + (rand() % 100);

  // Variables for Tier chance
  int tier1 = 0, tier2 = 0, tier3 = 0, tier4 = 0, tier5 = 0;

  // The first 5 rooms can spawn enemies Tier 1-2
  if (enemyProgression < 5)
  {
    if (randomTier <= 80)
      enemyTier = 1;
    else
      enemyTier = 2;
  }

  // The next 5 rooms can spawn enemies Tier 1-3
  else if (enemyProgression < 10)
  {
    // Calculates a random tier for the enemy - 60% chance of Tier 1, 30% chance of Tier 2, 10% chance of Tier 3
    tier1 = 60, tier2 = tier1 + 30;
    if (randomTier <= tier1)
      enemyTier = 1;
    else if (randomTier <= tier2)
      enemyTier = 2;
    else
      enemyTier = 3;
  }

  // The next 5 rooms can spawn enemies Tier 1-4
  else if (enemyProgression < 15)
  {
    // Calculates a random tier for the enemy - 35% chance of Tier 1, 30% chance of Tier 2, 25% chance of Tier 3, 10% chance of Tier 4
    tier1 = 35, tier2 = tier1 + 30, tier3 = tier2 + 25;
    if (randomTier <= tier1)
      enemyTier = 1;
    else if (randomTier <= tier2)
      enemyTier = 2;
    else if (randomTier <= tier3)
      enemyTier = 3;
    else
      enemyTier = 4;
  }

  // The final rooms can spawn enemies Tier 2-5
  else
  {
    // Calculates a random tier for the enemy - 35% chance of Tier 2, 25% chance of Tier 3, 20% chance of Tier 4, 15% chance of Tier 5, 5% chance of BOSS
    tier2 = 35, tier3 = tier2 + 25, tier4 = tier3 + 20, tier5 = tier4 + 15;
    if (randomTier <= tier2)
      enemyTier = 2;
    else if (randomTier <= tier3)
      enemyTier = 3;
    else if (randomTier <= tier4)
      enemyTier = 4;
    else if (randomTier <= tier5)
      enemyTier = 5;
    else
      boss = true;
  }

  // Establish non-boss enemy values
  if (!boss)
  {
    // Calculates health of the enemy based off of base enemy health and enemy tier
    enemyHealth = BASE_ENEMY_HEALTH * enemyTier;

    // Assigns a random name to the enemy
    int randomEnemyName = 0;
    int randomValue = 1 + (rand() % 100);
    if (enemyProgression < 5)
    {
      // 90% chance of enemies 1 - 2
      if (randomValue <= 90)
        randomEnemyName = 1 + (rand() % 2);
      // 10% chance of enemy 3
      else
        randomEnemyName = 3;
    }
    if (enemyProgression < 10)
    {
      // 70% chance of enemies 1 - 2
      if (randomValue <= 70)
        randomEnemyName = 1 + (rand() % 2);
      // 30% chance of enemy 3
      else
        randomEnemyName = 3;
    }
    else if (enemyProgression < 15)
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
        randomEnemyName = 1 + (rand() % 2) + randomValueAgain;
      }
      // 30% chance of enemy 3
      else
        randomEnemyName = 3;
    }
    else
    {
      // 40% chance of enemies 1 - 4
      if (randomValue <= 40)
        randomEnemyName = 1 + (rand() % 4);
      // 60% chance of enemies 4 - 6
      else
        randomEnemyName = 4 + (rand() % 3);
    }

    switch (randomEnemyName)
    {
      case 1:
      {
        enemyName = "Goblin"; // Weak to Melee, Neutral to Ranged, Neutral to Melee
        break;
      }
      case 2:
      {
        enemyName = "Orc"; // Weak to Magic, Neutral to Ranged, Neutral to Melee
        break;
      }
      case 3:
      {
        enemyName = "Troll"; // Weak to Ranged and Melee, Neutral to Magic
        enemyHealth *= 2;
        break;
      }
      case 4:
      {
        enemyName = "Skeleton"; // Weak to Melee, Neutral to Magic, Resistant to Ranged
        break;
      }
      case 5:
      {
        enemyName = "Cyclops"; // Neutral to Melee, Neutral to Magic, Neutral to Ranged
        break;
      }
      case 6:
      {
        enemyName = "Minotaur"; // Weak to Ranged and Magic, Resistant to Melee
        enemyHealth *= 2;
        break;
      }
    }

    // Print enemy attributes
    cout << "A tier " << enemyTier << " " << enemyName << " is guarding this room!\n\n";
    rewardTier = enemyTier; // Reward tier is used to control loot drops
  }

  // Establish enemy values as boss values
  else
  {
    // Boss health
    enemyHealth = BOSS_HEALTH;
    rewardTier = 10; // This value is only used to control loot drops
    int randomBossName = 1 + (rand() % 10);

    // Assigns a random boss name
    switch (randomBossName)
    {
      case 1:
      {
        enemyName = "Voidshaper Nihilus";
        break;
      }
      case 2:
      {
        enemyName = "Snarltooth the Feral";
        break;
      }
      case 3:
      {
        enemyName = "Dreadlord Vorkar";
        break;
      }
      case 4:
      {
        enemyName = "Soulstealer Malgrimor";
        break;
      }
      case 5:
      {
        enemyName = "King Rattleclaw";
        break;
      }
      case 6:
      {
        enemyName = "Ignatius the Infernal";
        break;
      }
      case 7:
      {
        enemyName = "Dreadmaw the Bonecrusher";
        break;
      }
      case 8:
      {
        enemyName = "Rotclaw the Pustulant";
        break;
      }
      case 9:
      {
        enemyName = "Sludgeheart the Grotesque";
        break;
      }
      case 10:
      {
        enemyName = "Drak'thar the Trollking";
        break;
      }
    }

    // Some cool boss spawning text
    cout << "\nThe Earth trembles beneath you, a powerful foe is near...\n"
         << enemyName << " has cornered you!\n\n";
  }
}x