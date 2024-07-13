#include "Enemy Resistance.h"

// Pre-condition: called by playerDamage(), passed damageValue, skill variables, enemy variables, and result of battleMenu()
// Post-condition: updates damageValue based on enemy stats
float enemyResistance(const string &abilityName, const string &enemyName, bool boss, int battleMenuSelection)
{
  float resistanceValue = 1.00;

  if (!boss)
  {
    if (enemyName == "Goblin")
    {
      switch (battleMenuSelection)
      {
        // Goblin is weak to Melee, but neutral to the rest
        case 1:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        default:
        {
          resistanceValue = 1.0;
          break;
        }
      }
    }
    else if (enemyName == "Orc")
    {
      switch (battleMenuSelection)
      {
        // Orc is weak to Magic, Neutral to the rest
        case 2:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        default:
        {
          resistanceValue = 1.0;
          break;
        }
      }
    }
    else if (enemyName == "Troll")
    {
      switch (battleMenuSelection)
      {
        // Troll is weak to Ranged and Melee, Neutral to Magic
        case 1:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        case 3:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        default:
        {
          resistanceValue = 1.0;
          break;
        }
      }
    }
    else if (enemyName == "Skeleton")
    {
      switch (battleMenuSelection)
      {
        // Skeleton is weak to Melee, Neutral to Magic, and Resistant to Ranged
        case 1:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        case 2:
        {
          resistanceValue = 1.0;
          break;
        }
        case 3:
        {
          resistanceValue = 0.5;
          cout << "\t" << abilityName << " is disappointingly ineffective against " << enemyName << "\n\n";
          break;
        }
      }
    }
    else if (enemyName == "Cyclops")
    {
      resistanceValue = 1.0;
    }
    else if (enemyName == "Minotaur")
    {
      switch (battleMenuSelection)
      {
        // Minotaur is weak to Ranged and Magic, Resistant to Melee
        case 1:
        {
          resistanceValue = 0.5;
          cout << "\t" << abilityName << " is disappointingly ineffective against " << enemyName << "\n\n";
          break;
        }
        case 2:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        case 3:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
      }
    }
  }

  // Players deal triple damage vs. bosses
  else
  {
    resistanceValue = 3.0;
  }

  return resistanceValue;
}