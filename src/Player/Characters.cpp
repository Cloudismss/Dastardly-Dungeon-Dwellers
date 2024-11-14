#include "Characters.h"

#include <iostream>

#include "Art.h"
#include "Globals.h"
#include "Validation.h"

#include "fmt/color.h"

using std::cin;
using std::cout;

Characters::Characters()
{
  // Allocate the head as a doubly linked circular list
  head = new Node;
  current = head;
  current->next = head;
  current->previous = head;

  // Set of available characters
  availableCharacters = {"Warrior", "Mage", "Archer", "Bard"};

  // Set the class name in the current node
  classSelection();

  // Remove selected class from available characters set
  availableCharacters.erase(availableCharacters.find(current->className));

  // Initialize character data
  current->maxHealth = 20.0;
  current->health = current->maxHealth;
  current->meleeWeapon = 1;
  current->magicWeapon = 1;
  current->rangedWeapon = 1;
  current->skills = new Skills(current->className);
}

Characters::~Characters()
{
  if (head)
  {
    current = head;
    Node *temp = nullptr;
    while(current->next != head)
    {
      temp = current->next;
      delete current->skills;
      delete current;
      current = temp;
    }
    delete head;
  }
}

void Characters::addCharacter()
{
  // Check set of available characters
  if (availableCharacters.empty())
    return;

  // Select random class name
  string className = " ";
  int classIndex = rand() % availableCharacters.size();
  set<string>::iterator iter = availableCharacters.begin();
  for (int i = 0; i != classIndex; ++i)
    ++iter;
  className = *iter;
  availableCharacters.erase(iter);

  // Connect pointers on doubly linked list
  Node *node = new Node;
  node->previous = current;
  node->next = head;
  current->next = node;
  head->previous = node;
  
  // Assign value
  node->className = className;
  node->skills = new Skills(className);

  // TODO: Output text indicating new character added
}

void Characters::cycle(char direction)
{
  if (direction == 'L')
    current = current->previous;
  else if (direction == 'R')
    current = current->next;
}

void Characters::select(const string &characterName)
{
  while (current->className != characterName)
    current = current->next;
}

// Pre-condition: passed className
// Post-condition: displays class selection menu and stores result in className
void Characters::classSelection()
{
  bool loopFlag = true;
  string tempClassName = " ";
  do
  {
    short int classChoice = 0;
    cout << ".-------------------------------------------------------------.\n"
         << "|                                                             |\n"
         << "|       Please choose a starting class using numbers 1-3:     |\n"
         << "|                                                             |\n"
         << "|            1. Warrior             Skill: Melee              |\n"
         << "|            2. Mage                Skill: Magic              |\n"
         << "|            3. Archer              Skill: Ranged             |\n"
         << "|                                                             |\n"
         << "'-------------------------------------------------------------'\n";
    cin >> classChoice;
    // High range is 999 to force the joke selection of bard if a number > 3 is entered
    if (validateInput(classChoice, 1, 999))
    {
      switch (classChoice)
      {
        // Player chose Warrior
        case 1:
        {
          setClassName("Warrior");
          warriorArt();
          break;
        }
        // Player chose Mage
        case 2:
        {
          setClassName("Mage");
          mageArt();
          break;
        }
        // Player chose Archer
        case 3:
        {
          setClassName("Archer");
          archerArt();
          break;
        }
        // Player chose an invalid number, and is auto-assigned to bard
        default:
        {
          setClassName("Bard");
          bardArt();
          cout << "That's wasn't an option >:(\n"
               << "Player has been punished and automatically assigned to class: 'Bard'\n\n";
          loopFlag = false;
          break;
        }
      }
    }

    // Confirm class selection
    if (loopFlag) // check is needed to skip bard confirm
      loopFlag = classSelectionConfirm();
    
  } while (loopFlag);
}

bool Characters::classSelectionConfirm()
{
  char confirmSelection = ' ';
  bool confirmLoop = true;
  do
  {
    cout << "You have selected '" << current->className << "', continue?\n"
          << "Y or N: ";
    cin >> confirmSelection;
    if (validateDecision(confirmSelection))
    {
      if (confirmSelection == 'Y' || confirmSelection == 'y')
      {
        cout << "\nYou've chosen the path of the " << current->className << "\n\n";
        confirmLoop = false;
      }
    }
  } while (confirmLoop);

  return confirmLoop;
}

void Characters::upgradeWeapon(const string &weaponType, const string &upgradeName)
{
  if (weaponType == "Melee")
    ++current->meleeWeapon;
  else if (weaponType == "Magic")
    ++current->magicWeapon;
  else if (weaponType == "Ranged")
    ++current->rangedWeapon;

  fmt::print(fmt::emphasis::bold, "{0} added\n", upgradeName);
}

short unsigned int Characters::getWeaponLevel(const string &weaponType)
{
  if (weaponType == "Melee")
    return current->meleeWeapon;
  else if (weaponType == "Magic")
    return current->magicWeapon;
  else if (weaponType == "Ranged")
    return current->rangedWeapon;

  // TODO: Implement clean fix for return in all control paths
  return -1;
}

short unsigned int Characters::getSkillLevel(const string &skillType)
{
  if (skillType == "Melee")
    return current->skills->meleeLevel;
  else if (skillType == "Magic")
    return current->skills->magicLevel;
  else if (skillType == "Ranged")
    return current->skills->rangedLevel;

  // TODO: Implement clean fix for return in all control paths
  return -1;
}

short unsigned int Characters::getSkillUpgrade(const string &skillType)
{
  // Check skill tier for damage calculations
  short unsigned int *skillCounter = nullptr;

  if (skillType == "Melee")
    skillCounter = &current->skills->meleeCounter;
  else if (skillType == "Magic")
    skillCounter = &current->skills->magicCounter;
  else if (skillType == "Ranged")
    skillCounter = &current->skills->rangedCounter;

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

string Characters::getSkillName(const string &skillType)
{
  if (skillType == "Melee")
    return current->skills->meleeName;
  else if (skillType == "Magic")
    return current->skills->magicName;
  else if (skillType == "Ranged")
    return current->skills->rangedName;

  // TODO: Implement clean fix for return in all control paths
  return "Error";
}

void Characters::useSkill(const string &skillType)
{
  short unsigned int *skillCounter = nullptr;

  if (skillType == "Melee")
    skillCounter = &current->skills->meleeCounter;
  else if (skillType == "Magic")
    skillCounter = &current->skills->magicCounter;
  else if (skillType == "Ranged")
    skillCounter = &current->skills->rangedCounter;

  if (*skillCounter + 1 == SKILL_UPGRADE || *skillCounter + 1 == SKILL_UPGRADE * 2)
  {
    // Upgrade messages for displayMeInABox function
    string congratulationsMessage = "Congratulations!";
    string upgradeMessage = " ";

    if (*skillCounter + 1 == SKILL_UPGRADE)
      setSkillName(skillType, upgradeMessage, 2);
    else if (*skillCounter + 1 == SKILL_UPGRADE * 2)
      setSkillName(skillType, upgradeMessage, 3);
      
    // Print skill upgrade notification
    displayMeInABox(congratulationsMessage, upgradeMessage);
  }
  ++(*skillCounter);
}

// Pre-condition: called by playerDamage(), passed skill variables, upgradeMessage, and tier override
// Post-condition: updates skillName and upgradeMessage based on tier and skillType
void Characters::setSkillName(const string &skillType, string &upgradeMessage, int tier)
{
  // Warrior Skills
  if (current->className == "Warrior")
  {
    switch (tier)
    {
      // Level 2 Skills
      case 2:
      {
        if (skillType == "Melee") // Slash | Cleave | Behemoth Strike
        {
          current->skills->meleeName = "Cleave";
          upgradeMessage = "Slash has been upgraded to Cleave";
        }
        else if (skillType == "Magic") // Shield Charge | Vortex Slam | Arcane Lunge
        {
          current->skills->magicName = "Vortex Slam";
          upgradeMessage = "Shield Charge has been upgraded to Vortex Slam";
        }
        else if (skillType == "Ranged") // Rock Throw | Shield Throw | Javelin Toss
        {
          current->skills->rangedName = "Shield Throw";
          upgradeMessage = "Rock Throw has been upgraded to Shield Throw";
        }
        break;
      }

      // Level 3 Skills
      case 3:
      {
        if (skillType == "Melee")
        {
          current->skills->meleeName = "Behemoth Strike";
          upgradeMessage = "Cleave has been upgraded to Behemoth Strike";
        }
        else if (skillType == "Magic")
        {
          current->skills->magicName = "Arcane Lunge";
          upgradeMessage = "Vortex Slam has been upgraded to Arcane Lunge";
        }
        else if (skillType == "Ranged")
        {
          current->skills->rangedName = "Javelin Toss";
          upgradeMessage = "Shield Throw has been upgraded to Javelin Toss";
        }
        break;
      }
    }
  }

  // Mage Skills
  else if (current->className == "Mage")
  {
    switch (tier)
    {
      // Level 2 Skills
      case 2:
      {
        if (skillType == "Melee") // Bonk | Whack | Astral Thump
        {
          current->skills->meleeName = "Whack";
          upgradeMessage = "Bonk has been upgraded to Whack";
        }
        else if (skillType == "Magic") // Frost Blast | Arctic Veil | Flash Freeze
        {
          current->skills->magicName = "Arctic Veil";
          upgradeMessage = "Frost Blast has been upgraded to Arctic Veil";
        }
        else if (skillType == "Ranged") // Zap | Thunderbolt | Thunderstorm
        {
          current->skills->rangedName = "Thunderbolt";
          upgradeMessage = "Zap has been upgraded to Thunderbolt";
        }
        break;
      }

      // Level 3 Skills
      case 3:
      {
        if (skillType == "Melee")
        {
          current->skills->meleeName = "Astral Thump";
          upgradeMessage = "Whack has been upgraded to Astral Thump";
        }
        else if (skillType == "Magic")
        {
          current->skills->magicName = "Flash Freeze";
          upgradeMessage = "Arctic Veil has been upgraded to Flash Freeze";
        }
        else if (skillType == "Ranged")
        {
          current->skills->rangedName = "Thunderstorm";
          upgradeMessage = "Thunderbolt has been upgraded to Thunderstorm";
        }
        break;
      }
    }
  }

  // Archer Skills
  else if (current->className == "Archer")
  {
    switch (tier)
    {
      // Level 2 Skills
      case 2:
      {
        if (skillType == "Melee") // Slice | Sever | Blade Dance
        {
          current->skills->meleeName = "Sever";
          upgradeMessage = "Slice has been upgraded to Sever";
        }
        else if (skillType == "Magic") // Poison Bomb | Intoxicate | Pestilence
        {
          current->skills->magicName = "Intoxicate";
          upgradeMessage = "Poison Bomb has been upgraded to Intoxicate";
        }
        else if (skillType == "Ranged") // Pierce | Perforate | Serpent Shot
        {
          current->skills->rangedName = "Perforate";
          upgradeMessage = "Pierce has been upgraded to Perforate";
        }
        break;
      }

      // Level 3 Skills
      case 3:
      {
        if (skillType == "Melee")
        {
          current->skills->meleeName = "Blade Dance";
          upgradeMessage = "Sever has been upgraded to Blade Dance";
        }
        else if (skillType == "Magic")
        {
          current->skills->magicName = "Pestilence";
          upgradeMessage = "Intoxicate has been upgraded to Pestilence";
        }
        else if (skillType == "Ranged")
        {
          current->skills->rangedName = "Serpent Shot";
          upgradeMessage = "Perforate has been upgraded to Serpent Shot";
        }
        break;
      }
    }
  }

  // Bard Skills
  else if (current->className == "Bard")
  {
    switch (tier)
    {
      // Level 2 Skills
      case 2:
      {
        if (skillType == "Melee") // Slap | Snuggle | Strum
        {
          current->skills->meleeName = "Snuggle";
          upgradeMessage = "Slap has been upgraded to Snuggle";
        }
        else if (skillType == "Magic") // Beg | Sing | Serenade
        {
          current->skills->magicName = "Sing";
          upgradeMessage = "Beg has been upgraded to Sing";
        }
        else if (skillType == "Ranged") // Waft | Whistle | Seduce
        {
          current->skills->rangedName = "Whistle";
          upgradeMessage = "Waft has been upgraded to Whistle";
        }
        break;
      }

      // Level 3 Skills
      case 3:
      {
        if (skillType == "Melee")
        {
          current->skills->meleeName = "Strum";
          upgradeMessage = "Snuggle has been upgraded to Strum";
        }
        else if (skillType == "Magic")
        {
          current->skills->magicName = "Serenade";
          upgradeMessage = "Sing has been upgraded to Serenade";
        }
        else if (skillType == "Ranged")
        {
          current->skills->rangedName = "Seduce";
          upgradeMessage = "Whistle has been upgraded to Seduce";
        }
        break;
      }
    }
  }
}
