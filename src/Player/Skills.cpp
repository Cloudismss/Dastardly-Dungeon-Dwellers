#include "Skills.h"

#include <iostream>
#include <fstream>

#include "Globals.h"

#include "Art.h"

Skills::Skills(const string &className)
{
  meleeName = " ";
  magicName = " ";
  rangedName = " ";
  meleeCounter = 0;
  magicCounter = 0;
  rangedCounter = 0;
  meleeSkill = 0;
  magicSkill = 0;
  rangedSkill = 0;
  critSkill = 1.0;
  initSkillNames(className);
  readSkills(className);
}

string Skills::getSkillName(const string &battleMenuSelection)
{
  if (battleMenuSelection == "Melee")
    return meleeName;
  else if (battleMenuSelection == "Magic")
    return magicName;
  else if (battleMenuSelection == "Ranged")
    return rangedName;

  // TODO: Implement clean fix for return in all control paths
  return "Error";
}

int Skills::getSkillTier(const string &battleMenuSelection)
{
  // Check skill tier for damage calculations
  short unsigned int *skillCounter = nullptr;

  if (battleMenuSelection == "Melee")
    skillCounter = &meleeCounter;
  else if (battleMenuSelection == "Magic")
    skillCounter = &magicCounter;
  else if (battleMenuSelection == "Ranged")
    skillCounter = &rangedCounter;

  // Level 1
  if (*skillCounter < SKILL_UPGRADE)
    return 1;
  // Level 2
  else if (*skillCounter >= SKILL_UPGRADE && *skillCounter < SKILL_UPGRADE * 2)
    return 2;
  // Level 3
  else if (*skillCounter >= SKILL_UPGRADE * 2)
    return 3;

  // TODO: Implement clean fix for return in all control paths
  return -1;
}

void Skills::useSkill(const string &battleMenuSelection, const string &className)
{
  short unsigned int *skillCounter = nullptr;

  if (battleMenuSelection == "Melee")
    skillCounter = &meleeCounter;
  else if (battleMenuSelection == "Magic")
    skillCounter = &magicCounter;
  else if (battleMenuSelection == "Ranged")
    skillCounter = &rangedCounter;

  if (*skillCounter + 1 == SKILL_UPGRADE || *skillCounter + 1 == SKILL_UPGRADE * 2)
  {
    // Upgrade messages for displayMeInABox function
    string congratulationsMessage = "Congratulations!";
    string upgradeMessage = " ";

    if (*skillCounter + 1 == SKILL_UPGRADE)
      setSkillName(battleMenuSelection, upgradeMessage, className, 2);
    else if (*skillCounter + 1 == SKILL_UPGRADE * 2)
      setSkillName(battleMenuSelection, upgradeMessage, className, 3);
      
    // Print skill upgrade notification
    displayMeInABox(congratulationsMessage, upgradeMessage);
  }
  ++(*skillCounter);
}

void Skills::readSkills(const string &className)
{
  // Load Character Stats.txt or create and load Character Stats.txt with defaults, the player can edit the .txt file if they want custom stats
  std::ifstream characterStats;
  characterStats.open("Character Stats.txt");
  if (!characterStats)
  {
    std::ofstream defaultCharacterStats;
    defaultCharacterStats.open("Character Stats.txt");
    generateSkills(defaultCharacterStats);
    defaultCharacterStats.close();
    characterStats.open("Character Stats.txt");
    if (!characterStats)
    {
      std::cerr << "Character Stats.txt failed to open!\n";
    }
  }

  string classNameChecker = " ";
  
  // Ignore the first two lines (info header and blank line)
  getline(characterStats, classNameChecker);
  getline(characterStats, classNameChecker);
  while (characterStats.good())
  {
    // Read the class name
    getline(characterStats, classNameChecker, ',');
    // Check the class name
    if (classNameChecker == className)
      characterStats >> meleeSkill >> rangedSkill >> magicSkill >> critSkill;
    // Check the next line if className doesn't match
    else
      getline(characterStats, classNameChecker);
  }

  characterStats.close();
}

// Pre-condition: valid output file open
// Post-condition: writes default character stats to created file "Character Stats.txt"
void Skills::generateSkills(std::ofstream &defaultCharacterStats)
{
  defaultCharacterStats << "Class Name, Melee Skill | Magic Skill | Ranged Skill | Crit Skill\n"
                        << "\n"
                        << "Warrior, 3 2 2 1.0\n"
                        << "Mage, 1 3 2 3.0\n"
                        << "Archer, 2 2 3 1.0\n"
                        << "Bard, 1 1 1 9.0";
}

void Skills::initSkillNames(const string &className)
{
  // Warrior Skills
  if (className == "Warrior")
  {
    meleeName = "Slash";
    magicName = "Shield Charge";
    rangedName = "Rock Throw";
  }

  // Mage Skills
  else if (className == "Mage")
  {
    meleeName = "Bonk";
    magicName = "Frost Blast";
    rangedName = "Zap";
  }

  // Archer Skills
  else if (className == "Archer")
  {
    meleeName = "Slice";
    magicName = "Poison Bomb";
    rangedName = "Pierce";
  }

  // Bard Skills
  else if (className == "Bard")
  {
      meleeName = "Slap";
      magicName = "Beg";
      rangedName = "Waft";
  }
}

// Pre-condition: called by playerDamage(), passed skill variables, upgradeMessage, and tier override
// Post-condition: updates skillName and upgradeMessage based on tier and skillType
void Skills::setSkillName(const string &skillType, string &upgradeMessage, const string &className, int tier)
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
          meleeName = "Cleave";
          upgradeMessage = "Slash has been upgraded to Cleave";
        }
        else if (skillType == "Magic") // Shield Charge | Vortex Slam | Arcane Lunge
        {
          magicName = "Vortex Slam";
          upgradeMessage = "Shield Charge has been upgraded to Vortex Slam";
        }
        else if (skillType == "Ranged") // Rock Throw | Shield Throw | Javelin Toss
        {
          rangedName = "Shield Throw";
          upgradeMessage = "Rock Throw has been upgraded to Shield Throw";
        }
        break;
      }

      // Level 3 Skills
      case 3:
      {
        if (skillType == "Melee")
        {
          meleeName = "Behemoth Strike";
          upgradeMessage = "Cleave has been upgraded to Behemoth Strike";
        }
        else if (skillType == "Magic")
        {
          magicName = "Arcane Lunge";
          upgradeMessage = "Vortex Slam has been upgraded to Arcane Lunge";
        }
        else if (skillType == "Ranged")
        {
          rangedName = "Javelin Toss";
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
          meleeName = "Whack";
          upgradeMessage = "Bonk has been upgraded to Whack";
        }
        else if (skillType == "Magic") // Frost Blast | Arctic Veil | Flash Freeze
        {
          magicName = "Arctic Veil";
          upgradeMessage = "Frost Blast has been upgraded to Arctic Veil";
        }
        else if (skillType == "Ranged") // Zap | Thunderbolt | Thunderstorm
        {
          rangedName = "Thunderbolt";
          upgradeMessage = "Zap has been upgraded to Thunderbolt";
        }
        break;
      }

      // Level 3 Skills
      case 3:
      {
        if (skillType == "Melee")
        {
          meleeName = "Astral Thump";
          upgradeMessage = "Whack has been upgraded to Astral Thump";
        }
        else if (skillType == "Magic")
        {
          magicName = "Flash Freeze";
          upgradeMessage = "Arctic Veil has been upgraded to Flash Freeze";
        }
        else if (skillType == "Ranged")
        {
          rangedName = "Thunderstorm";
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
          meleeName = "Sever";
          upgradeMessage = "Slice has been upgraded to Sever";
        }
        else if (skillType == "Magic") // Poison Bomb | Intoxicate | Pestilence
        {
          magicName = "Intoxicate";
          upgradeMessage = "Poison Bomb has been upgraded to Intoxicate";
        }
        else if (skillType == "Ranged") // Pierce | Perforate | Serpent Shot
        {
          rangedName = "Perforate";
          upgradeMessage = "Pierce has been upgraded to Perforate";
        }
        break;
      }

      // Level 3 Skills
      case 3:
      {
        if (skillType == "Melee")
        {
          meleeName = "Blade Dance";
          upgradeMessage = "Sever has been upgraded to Blade Dance";
        }
        else if (skillType == "Magic")
        {
          magicName = "Pestilence";
          upgradeMessage = "Intoxicate has been upgraded to Pestilence";
        }
        else if (skillType == "Ranged")
        {
          rangedName = "Serpent Shot";
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
          meleeName = "Snuggle";
          upgradeMessage = "Slap has been upgraded to Snuggle";
        }
        else if (skillType == "Magic") // Beg | Sing | Serenade
        {
          magicName = "Sing";
          upgradeMessage = "Beg has been upgraded to Sing";
        }
        else if (skillType == "Ranged") // Waft | Whistle | Seduce
        {
          rangedName = "Whistle";
          upgradeMessage = "Waft has been upgraded to Whistle";
        }
        break;
      }

      // Level 3 Skills
      case 3:
      {
        if (skillType == "Melee")
        {
          meleeName = "Strum";
          upgradeMessage = "Snuggle has been upgraded to Strum";
        }
        else if (skillType == "Magic")
        {
          magicName = "Serenade";
          upgradeMessage = "Sing has been upgraded to Serenade";
        }
        else if (skillType == "Ranged")
        {
          rangedName = "Seduce";
          upgradeMessage = "Whistle has been upgraded to Seduce";
        }
        break;
      }
    }
  }
}