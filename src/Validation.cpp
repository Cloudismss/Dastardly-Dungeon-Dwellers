#include "Validation.h"

// Pre-condition: called to validate a Y or N decision
// Post-condition: returns whether the choice was valid or not
bool validateDecision(int userChoice)
{
  bool validFlag = true;
  if ((cin.fail()) || (!(userChoice == 'Y' || userChoice == 'y' || userChoice == 'N' || userChoice == 'n')))
  {
    cout << setw(63) << "Invalid Selection! >:(\n"
         << setw(63) << "Please enter an acceptable value\n"
         << "\n";
    validFlag = false;
  }
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return validFlag;
}

// Pre-condition: called to validate a number input
// Post-condition: returns whether the choice was valid or not
bool validateInput(int userChoice, int rangeLow, int rangeHigh)
{
  bool validFlag = true;
  if ((cin.fail()) || ((userChoice < rangeLow) || (userChoice > rangeHigh)))
  {
    cout << setw(63) << "Invalid Selection! >:( \n"
         << setw(63) << "Please enter an acceptable value\n"
         << "\n";
    validFlag = false;
  }
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return validFlag;
}

// Pre-condition: called to validate a direction input, passed userChoice
// Post-condition: returns whether the choice was valid or not, updates userChoice value to uppercase
bool validateDirection(int rowPosition, int columnPosition, char &userChoice)
{
  bool validFlag = true;
  if ((cin.fail()) || (!(userChoice == 'N' || userChoice == 'n' || userChoice == 'E' || userChoice == 'e' || userChoice == 'S' || userChoice == 's' || userChoice == 'W' || userChoice == 'w')))
  {
    cout << setw(63) << "Invalid Selection! >:(\n"
         << setw(63) << "Please enter an acceptable value\n"
         << "\n";
    validFlag = false;
  }
  else
  {
    // Convert the char to uppercase for use in switch statements
    if (userChoice == 'n' || userChoice == 'e' || userChoice == 's' || userChoice == 'w')
    {
      userChoice -= 32;
    }

    // Bounds checking
    string boundsFail = "A mysterious force prevents you from progressing in that direction...\n\n";
    switch (userChoice)
    {
      case 'N':
      {
        if (--rowPosition < 0)
        {
          cout << boundsFail;
          validFlag = false;
        }
        break;
      }
      case 'S':
      {
        if (++rowPosition > MAP_ROWS - 1)
        {
          cout << boundsFail;
          validFlag = false;
        }
        break;
      }
      case 'E':
      {
        if (++columnPosition > MAP_COLUMNS - 1)
        {
          cout << boundsFail;
          validFlag = false;
        }
        break;
      }
      case 'W':
      {
        if (--columnPosition < 0)
        {
          cout << boundsFail;
          validFlag = false;
        }
        break;
      }
    }
  }
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return validFlag;
}