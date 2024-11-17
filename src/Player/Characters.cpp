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
  current->skills = new Skills(current->className);
  current->health = current->skills->maxHealth;
  current->level = 1;
  current->xp = 0;
  current->meleeWeapon = 1;
  current->magicWeapon = 1;
  current->rangedWeapon = 1;
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

  // Pause the screen until the user is ready to play
  cout << "Press enter to begin your journey: ";
  string enterKey = " ";
  getline(cin, enterKey);
  cout << "\n";
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

void Characters::addXp(int xpAdjust)
{
  cout << current->className << " gained " << xpAdjust << " xp!\n";

  // XP amount exceeds a full level
  while(xpAdjust >= xpRequiredPerLevel)
  {
    addLevel();
    xpAdjust -= xpRequiredPerLevel;
  }

  // Player levels up with adkustment
  if (current->xp + xpAdjust >= xpRequiredPerLevel)
  {
    int difference = xpRequiredPerLevel - current->xp;
    xpAdjust -= difference;
    addLevel();
    current->xp = 0;
  }

  current->xp += xpAdjust;

  cout << "\n";
}

void Characters::addLevel()
{
  cout << current->className << " is now level " << ++current->level << "!\n";
  
  ++current->skills->meleeLevel;
  ++current->skills->magicLevel;
  ++current->skills->rangedLevel;
  ++current->skills->critLevel;
  current->skills->maxHealth += 2;
  current->health += 2;
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
  // Add 1 since upgradeTiers start at index 0
  if (skillType == "Melee")
    return current->skills->meleeUpgradeTier + 1;
  else if (skillType == "Magic")
    return current->skills->magicUpgradeTier + 1;
  else if (skillType == "Ranged")
    return current->skills->magicUpgradeTier + 1;

  // TODO: Implement clean fix for return in all control paths
  return -1;
}

string Characters::getSkillName(const string &skillType)
{
  if (skillType == "Melee")
    return current->skills->skillNames[skillType][current->skills->meleeUpgradeTier];
  else if (skillType == "Magic")
    return current->skills->skillNames[skillType][current->skills->magicUpgradeTier];
  else if (skillType == "Ranged")
    return current->skills->skillNames[skillType][current->skills->rangedUpgradeTier];

  // TODO: Implement clean fix for return in all control paths
  return "Error";
}

void Characters::useSkill(const string &skillType)
{
  short unsigned int *upgradeCounter = nullptr;

  if (skillType == "Melee")
    upgradeCounter = &current->skills->meleeCounter;
  else if (skillType == "Magic")
    upgradeCounter = &current->skills->magicCounter;
  else if (skillType == "Ranged")
    upgradeCounter = &current->skills->rangedCounter;

  if (*upgradeCounter + 1 == SKILL_UPGRADE || *upgradeCounter + 1 == SKILL_UPGRADE * 2)
    upgradeSkillName(skillType);

  ++(*upgradeCounter);
}

void Characters::upgradeSkillName(const string &skillType)
{
  short unsigned int *skillUpgradeTier = nullptr;

  if (skillType == "Melee")
    skillUpgradeTier = &current->skills->meleeUpgradeTier;
  else if (skillType == "Magic")
    skillUpgradeTier = &current->skills->magicUpgradeTier;
  else if (skillType == "Ranged")
    skillUpgradeTier = &current->skills->rangedUpgradeTier;

  const string upgradeMessage = current->skills->skillNames[skillType][*skillUpgradeTier] + " has been upgraded to " + current->skills->skillNames[skillType][(*skillUpgradeTier) + 1];
  ++(*skillUpgradeTier);
 
  // Print skill upgrade notification
  displayMeInABox("Congratulations!", upgradeMessage);
}
