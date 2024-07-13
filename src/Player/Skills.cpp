#include "Skills.h"

// Pre-condition: called by playerDamage(), passed skill variables, upgradeMessage, and tier override
// Post-condition: updates skillName and upgradeMessage based on tier and skillType
void skillNames(string &skillName, const string &skillType, string &upgradeMessage, const string &className, int tier)
{
  // Function was called to upgrade the skill
  if (tier > 1)
  {
    // Warrior Skills
    if (className == "Warrior")
    {
      switch (tier)
      {
        // Level 2 Skills
        case 2:
        {
          if (skillType == "Melee") // Slash | Cleave | Behemoth Strike
          {
            skillName = "Cleave";
            upgradeMessage = "Slash has been upgraded to Cleave";
          }
          else if (skillType == "Magic") // Shield Charge | Vortex Slam | Arcane Lunge
          {
            skillName = "Vortex Slam";
            upgradeMessage = "Shield Charge has been upgraded to Vortex Slam";
          }
          else if (skillType == "Ranged") // Rock Throw | Shield Throw | Javelin Toss
          {
            skillName = "Shield Throw";
            upgradeMessage = "Rock Throw has been upgraded to Shield Throw";
          }
          break;
        }

        // Level 3 Skills
        case 3:
        {
          if (skillType == "Melee")
          {
            skillName = "Behemoth Strike";
            upgradeMessage = "Cleave has been upgraded to Behemoth Strike";
          }
          else if (skillType == "Magic")
          {
            skillName = "Arcane Lunge";
            upgradeMessage = "Vortex Slam has been upgraded to Arcane Lunge";
          }
          else if (skillType == "Ranged")
          {
            skillName = "Javelin Toss";
            upgradeMessage = "Shield Throw has been upgraded to Javelin Toss";
          }
          break;
        }
      }
    }

    // Mage Skills
    else if (className == "Mage")
    {
      switch (tier)
      {
        // Level 2 Skills
        case 2:
        {
          if (skillType == "Melee") // Bonk | Whack | Astral Thump
          {
            skillName = "Whack";
            upgradeMessage = "Bonk has been upgraded to Whack";
          }
          else if (skillType == "Magic") // Frost Blast | Arctic Veil | Flash Freeze
          {
            skillName = "Arctic Veil";
            upgradeMessage = "Frost Blast has been upgraded to Arctic Veil";
          }
          else if (skillType == "Ranged") // Zap | Thunderbolt | Thunderstorm
          {
            skillName = "Thunderbolt";
            upgradeMessage = "Zap has been upgraded to Thunderbolt";
          }
          break;
        }

        // Level 3 Skills
        case 3:
        {
          if (skillType == "Melee")
          {
            skillName = "Astral Thump";
            upgradeMessage = "Whack has been upgraded to Astral Thump";
          }
          else if (skillType == "Magic")
          {
            skillName = "Flash Freeze";
            upgradeMessage = "Arctic Veil has been upgraded to Flash Freeze";
          }
          else if (skillType == "Ranged")
          {
            skillName = "Thunderstorm";
            upgradeMessage = "Thunderbolt has been upgraded to Thunderstorm";
          }
          break;
        }
      }
    }

    // Archer Skills
    else if (className == "Archer")
    {
      switch (tier)
      {
        // Level 2 Skills
        case 2:
        {
          if (skillType == "Melee") // Slice | Sever | Blade Dance
          {
            skillName = "Sever";
            upgradeMessage = "Slice has been upgraded to Sever";
          }
          else if (skillType == "Magic") // Poison Bomb | Intoxicate | Pestilence
          {
            skillName = "Intoxicate";
            upgradeMessage = "Poison Bomb has been upgraded to Intoxicate";
          }
          else if (skillType == "Ranged") // Pierce | Perforate | Serpent Shot
          {
            skillName = "Perforate";
            upgradeMessage = "Pierce has been upgraded to Perforate";
          }
          break;
        }

        // Level 3 Skills
        case 3:
        {
          if (skillType == "Melee")
          {
            skillName = "Blade Dance";
            upgradeMessage = "Sever has been upgraded to Blade Dance";
          }
          else if (skillType == "Magic")
          {
            skillName = "Pestilence";
            upgradeMessage = "Intoxicate has been upgraded to Pestilence";
          }
          else if (skillType == "Ranged")
          {
            skillName = "Serpent Shot";
            upgradeMessage = "Perforate has been upgraded to Serpent Shot";
          }
          break;
        }
      }
    }

    // Bard Skills
    else if (className == "Bard")
    {
      switch (tier)
      {
        // Level 2 Skills
        case 2:
        {
          if (skillType == "Melee") // Slap | Snuggle | Strum
          {
            skillName = "Snuggle";
            upgradeMessage = "Slap has been upgraded to Snuggle";
          }
          else if (skillType == "Magic") // Beg | Sing | Serenade
          {
            skillName = "Sing";
            upgradeMessage = "Beg has been upgraded to Sing";
          }
          else if (skillType == "Ranged") // Waft | Whistle | Seduce
          {
            skillName = "Whistle";
            upgradeMessage = "Waft has been upgraded to Whistle";
          }
          break;
        }

        // Level 3 Skills
        case 3:
        {
          if (skillType == "Melee")
          {
            skillName = "Strum";
            upgradeMessage = "Snuggle has been upgraded to Strum";
          }
          else if (skillType == "Magic")
          {
            skillName = "Serenade";
            upgradeMessage = "Sing has been upgraded to Serenade";
          }
          else if (skillType == "Ranged")
          {
            skillName = "Seduce";
            upgradeMessage = "Whistle has been upgraded to Seduce";
          }
          break;
        }
      }
    }
  }

  // Function was called to initialize skill names
  else
  {
    // Warrior Skills
    if (className == "Warrior")
    {
      if (skillType == "Melee")
      {
        skillName = "Slash";
      }
      else if (skillType == "Magic")
      {
        skillName = "Shield Charge";
      }
      else if (skillType == "Ranged")
      {
        skillName = "Rock Throw";
      }
    }

    // Mage Skills
    else if (className == "Mage")
    {
      if (skillType == "Melee")
      {
        skillName = "Bonk";
      }
      else if (skillType == "Magic")
      {
        skillName = "Frost Blast";
      }
      else if (skillType == "Ranged")
      {
        skillName = "Zap";
      }
    }

    // Archer Skills
    else if (className == "Archer")
    {
      if (skillType == "Melee")
      {
        skillName = "Slice";
      }
      else if (skillType == "Magic")
      {
        skillName = "Poison Bomb";
      }
      else if (skillType == "Ranged")
      {
        skillName = "Pierce";
      }
    }

    // Bard Skills
    else if (className == "Bard")
    {
      if (skillType == "Melee")
      {
        skillName = "Slap";
      }
      else if (skillType == "Magic")
      {
        skillName = "Beg";
      }
      else if (skillType == "Ranged")
      {
        skillName = "Waft";
      }
    }
  }
}