#include "Characters.h"

#include <iostream>

#include "Art.h"
#include "Validation.h"

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
