#include "Character List.h"

#include <iostream>

#include "Art.h"
#include "Validation.h"

#include "Archer.h"
#include "Bard.h"
#include "Mage.h"
#include "Warrior.h"

using std::cin;
using std::cout;

CharacterList::CharacterList()
{
  // Set the class name in the current node and initialize the head
  addSpecificCharacter(classSelection());
}

CharacterList::~CharacterList()
{
  if (head->next == head)
  {
    delete head;
    head = nullptr;
  }
  else
  {
    current = head;
    Node *temp = nullptr;
    while(current->next != head)
    {
      temp = current->next;
      delete current;
      current = temp;
    }
    delete head;
    head = nullptr;
  }
}

void CharacterList::addRandomCharacter()
{
  // Check if any characters are available
  string className = Character::getRandomAvailableCharacter();
  if (className == "None")
    return;

  // Connect pointers on doubly linked list
  Node *node = nullptr;
  if (!head)
  {
    head = new Node;
    current = node = head;
    current->next = head;
    current->previous = head;
  }
  else 
  {
    node = new Node;
    node->previous = current;
    node->next = head;
    current->next = node;
    head->previous = node;
  }

  // Remove character from list of available characters
  Character::checkoutCharacter(className);
  
  if (className == "Archer")
    node->character = new Archer;
  else if (className == "Bard")
    node->character = new Bard;
  else if (className == "Mage")
    node->character = new Mage;
  else if (className == "Warrior")
    node->character = new Warrior;

  // TODO: Output text indicating new character added
  cout << className << " has joined your party\n\n";
}

void CharacterList::addSpecificCharacter(const string &className)
{
  // Check if any characters are available
  if (!Character::getAvailableCharacter(className))
    return;

  // Connect pointers on doubly linked list
  Node *node = nullptr;
  if (!head)
  {
    head = new Node;
    current = node = head;
    current->next = head;
    current->previous = head;
  }
  else 
  {
    node = new Node;
    node->previous = current;
    node->next = head;
    current->next = node;
    head->previous = node;
  }

  // Remove character from list of available characters
  Character::checkoutCharacter(className);
  
  if (className == "Archer")
    node->character = new Archer;
  else if (className == "Bard")
    node->character = new Bard;
  else if (className == "Mage")
    node->character = new Mage;
  else if (className == "Warrior")
    node->character = new Warrior;

  // TODO: Output text indicating new character added
  cout << className << " has joined your party\n\n";
}

bool CharacterList::removeCurrentCharacter()
{
  if (head->next == head)
    return false; // Out of characters

  Node *temp = current;

  temp->previous->next = temp->next;
  temp->next->previous = temp->previous;
  delete temp;
  temp = nullptr;

  return true;
}

bool CharacterList::removeSpecificCharacter(const string &className)
{
  if (head->next == head)
    return false; // Out of characters

  Node *temp = head;

  while (temp->character->getClassName() != className && temp->next != temp)
    temp = temp->next;

  temp->previous->next = temp->next;
  temp->next->previous = temp->previous;
  delete temp;
  temp = nullptr;

  return true;
}

bool CharacterList::cycle(char direction)
{
  if (current->next == current)
    return false;

  Node *previous = current;

  if (direction == 'L')
    current = current->previous;
  else if (direction == 'R')
    current = current->next;

  cout << previous->character->getClassName() << " is tired, your turn " << current->character->getClassName() << "\n\n";

  return true;
}

void CharacterList::select(const string &characterName)
{
  while (current->character->getClassName() != characterName && current->next != current)
    current = current->next;
}

// Pre-condition: passed className
// Post-condition: displays class selection menu and stores result in className
string CharacterList::classSelection()
{
  bool loopFlag = true;
  string className = " ";
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
          className = "Warrior";
          warriorArt();
          break;
        }
        // Player chose Mage
        case 2:
        {
          className = "Mage";
          mageArt();
          break;
        }
        // Player chose Archer
        case 3:
        {
          className = "Archer";
          archerArt();
          break;
        }
        // Player chose an invalid number, and is auto-assigned to bard
        default:
        {
          className = "Bard";
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
      loopFlag = classSelectionConfirm(className);
    
  } while (loopFlag);

  return className;
}

bool CharacterList::classSelectionConfirm(const string &className)
{
  char confirmSelection = ' ';
  bool confirmLoop = true;
  do
  {
    cout << "You have selected '" << className << "', continue?\n"
          << "Y or N: ";
    cin >> confirmSelection;
    if (validateDecision(confirmSelection))
    {
      if (confirmSelection == 'Y' || confirmSelection == 'y')
      {
        cout << "\nYou've chosen the path of the " << className << "\n\n";
        confirmLoop = false;
      }
    }
  } while (confirmLoop);

  return confirmLoop;
}
