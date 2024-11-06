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

  // Set the class name in the current node
  classSelection();
  current->health = 20.0;
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

void Characters::append(const string &className)
{
  // Connect pointers on doubly linked list
  Node *node = new Node;
  node->previous = current;
  node->next = head;
  current->next = node;
  head->previous = node;
  
  // Assign value
  node->className = className;
  node->skills = new Skills(className);
}

void Characters::cycle(char direction)
{
  if (direction == 'L')
    current = current->previous;
  else if (direction == 'R')
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
          tempClassName = "Warrior";
          warriorArt();
          break;
        }
        // Player chose Mage
        case 2:
        {
          tempClassName = "Mage";
          mageArt();
          break;
        }
        // Player chose Archer
        case 3:
        {
          tempClassName = "Archer";
          archerArt();
          break;
        }
        // Player chose an invalid number, and is auto-assigned to bard
        default:
        {
          tempClassName = "Bard";
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

  // Set class name
  setClassName(tempClassName);
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