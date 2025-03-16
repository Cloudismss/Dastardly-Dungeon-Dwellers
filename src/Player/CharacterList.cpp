#include "CharacterList.h"

#include <iostream>
#include <string>

#include "BoxArt.h"
#include "CharacterArt.h"

#include "Archer.h"
#include "Bard.h"
#include "Mage.h"
#include "Warrior.h"

#include "Validation.h"

CharacterList::CharacterList()
{
  // Set the class name in the current node and initialize the head
  appendCharacter(classSelection());
}

CharacterList::~CharacterList()
{
  if (head->next == head)
    delete head;
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
  }
  current = nullptr;
  head = nullptr;
}

void CharacterList::appendRandomCharacter()
{
  // Check if any characters are available
  std::string className = Character::getRandomAvailableCharacter();
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
    Node *last;
    if (head->previous == head)
      last = head;
    else
      last = head->previous;

    node = new Node;
    head->previous = node;
    node->next = head;
    node->previous = last;
    last->next = node;
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
  std::string message = className + " has joined your party!";
  art::box::displayMeInABox(message);
}

void CharacterList::appendCharacter(const std::string &className)
{
  // Check if any characters are available
  if (!Character::getAvailability(className))
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
    Node *last;
    if (head->previous == head)
      last = head;
    else
      last = head->previous;

    node = new Node;
    head->previous = node;
    node->next = head;
    node->previous = last;
    last->next = node;

    // TODO: Output text indicating new character added
    std::string message = className + " has joined your party!";
    art::box::displayMeInABox(message);
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
}

bool CharacterList::removeCurrentCharacter()
{
  if (head->next == head)
    return false; // Out of characters

  if (current == head)
    head = current->next; // Need to reassign the head since it is deleted in the destructor

  Node *temp = current;

  // Cycle to next character
  if (!cycle('R', "Delete"))
    return false;

  temp->previous->next = temp->next;
  temp->next->previous = temp->previous;
  delete temp;
  temp = nullptr;

  return true;
}

bool CharacterList::removeCharacter(const std::string &className)
{
  if (head->next == head)
    return false; // Out of characters

  if (current == head)
    head = current->next; // Need to reassign the head since it is deleted in the destructor

  Node *temp = head;

  while (temp->character->getClassName() != className && temp->next != temp)
    temp = temp->next;

  temp->previous->next = temp->next;
  temp->next->previous = temp->previous;
  delete temp;
  temp = nullptr;

  return true;
}

bool CharacterList::cycle(char direction, const std::string &context)
{
  if (current->next == current)
    return false;

  Node *previous = current;

  if (direction == 'L')
    current = current->previous;
  else if (direction == 'R')
    current = current->next;
  
  if (context == "Switch") // This is just a check for context based newline output formatting
    std::cout << "\n\t" << previous->character->getClassName() << " is tired, you're up " << current->character->getClassName() << "!\n";
  else
    std::cout << "\t" << previous->character->getClassName() << " is tired, you're up " << current->character->getClassName() << "!\n\n";

  return true;
}

void CharacterList::select(const std::string &characterName)
{
  while (current->character->getClassName() != characterName && current->next != current)
    current = current->next;
}

std::string CharacterList::classSelection() const
{
  bool loopFlag = true;
  std::string className = " ";
  do
  {
    int classChoice = 0;
    std::cout << ".-------------------------------------------------------------.\n"
         << "|                                                             |\n"
         << "|       Please choose a starting class using numbers 1-3:     |\n"
         << "|                                                             |\n"
         << "|            1: Warrior             Skill: Melee              |\n"
         << "|            2: Mage                Skill: Magic              |\n"
         << "|            3: Archer              Skill: Ranged             |\n"
         << "|                                                             |\n"
         << "'-------------------------------------------------------------'\n";
    std::cin >> classChoice;
    // High range is 999 to force the joke selection of bard if a number > 3 is entered
    if (validateInput(classChoice, 1, 999))
    {
      switch (classChoice)
      {
        case 1:
        {
          className = "Warrior";
          art::character::warrior();
          break;
        }
        case 2:
        {
          className = "Mage";
          art::character::mage();
          break;
        }
        case 3:
        {
          className = "Archer";
          art::character::archer();
          break;
        }
        // Player chose an invalid number, and is auto-assigned to bard
        default:
        {
          className = "Bard";
          art::character::bard();
          std::cout << "That wasn't an option >:(\n"
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

bool CharacterList::classSelectionConfirm(const std::string &className) const
{
  char confirmSelection = ' ';
  bool confirmLoop = true;
  do
  {
    std::cout << "You have selected '" << className << "', continue?\n"
          << "Y or N: ";
    std::cin >> confirmSelection;
    if (validateDecision(confirmSelection))
    {
      if (confirmSelection == 'Y' || confirmSelection == 'y')
      {
        std::cout << "\nYou've chosen the path of the " << className << "\n\n";
        return false; // Exit main character select loop
      }
      return true; // Return to beginning of character select loop
    }
  } while (confirmLoop);
  
  // TODO: Clean solution for return in all control paths
  return true;
}
