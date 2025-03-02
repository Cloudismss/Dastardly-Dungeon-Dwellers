#include "Validation.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using std::cin;
using std::cout;
using std::setw;
using std::string;

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

bool validateDirection(int rowPos, int colPos, char &userChoice, const int ROWS, const int COLS)
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
      userChoice -= 32;

    // Bounds checking
    string boundsFail = "A mysterious force prevents you from progressing in that direction...\n\n";
    switch (userChoice)
    {
      case 'N':
      {
        if (--rowPos < 0)
        {
          cout << boundsFail;
          validFlag = false;
        }
        break;
      }
      case 'S':
      {
        if (++rowPos > ROWS - 1)
        {
          cout << boundsFail;
          validFlag = false;
        }
        break;
      }
      case 'E':
      {
        if (++colPos > COLS - 1)
        {
          cout << boundsFail;
          validFlag = false;
        }
        break;
      }
      case 'W':
      {
        if (--colPos < 0)
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
