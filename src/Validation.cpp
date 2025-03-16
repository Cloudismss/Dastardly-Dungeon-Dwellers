#include "Validation.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

namespace validate
{
  bool decision(int userChoice)
  {
    bool validFlag = true;
    if ((std::cin.fail()) || (!(userChoice == 'Y' || userChoice == 'y' || userChoice == 'N' || userChoice == 'n')))
    {
      std::cout << std::setw(63) << "Invalid Selection! >:(\n"
           << std::setw(63) << "Please enter an acceptable value\n"
           << "\n";
      validFlag = false;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return validFlag;
  }
  
  bool input(int userChoice, int rangeLow, int rangeHigh)
  {
    bool validFlag = true;
    if ((std::cin.fail()) || ((userChoice < rangeLow) || (userChoice > rangeHigh)))
    {
      std::cout << std::setw(63) << "Invalid Selection! >:( \n"
           << std::setw(63) << "Please enter an acceptable value\n"
           << "\n";
      validFlag = false;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return validFlag;
  }
  
  bool direction(int rowPos, int colPos, char &userChoice, const int ROWS, const int COLS)
  {
    bool validFlag = true;
    if ((std::cin.fail()) || (!(userChoice == 'N' || userChoice == 'n' || userChoice == 'E' || userChoice == 'e' || userChoice == 'S' || userChoice == 's' || userChoice == 'W' || userChoice == 'w')))
    {
      std::cout << std::setw(63) << "Invalid Selection! >:(\n"
           << std::setw(63) << "Please enter an acceptable value\n"
           << "\n";
      validFlag = false;
    }
    else
    {
      // Convert the char to uppercase for use in switch statements
      if (userChoice == 'n' || userChoice == 'e' || userChoice == 's' || userChoice == 'w')
        userChoice -= 32;
  
      // Bounds checking
      std::string boundsFail = "A mysterious force prevents you from progressing in that direction...\n\n";
      switch (userChoice)
      {
        case 'N':
        {
          if (--rowPos < 0)
          {
            std::cout << boundsFail;
            validFlag = false;
          }
          break;
        }
        case 'S':
        {
          if (++rowPos > ROWS - 1)
          {
            std::cout << boundsFail;
            validFlag = false;
          }
          break;
        }
        case 'E':
        {
          if (++colPos > COLS - 1)
          {
            std::cout << boundsFail;
            validFlag = false;
          }
          break;
        }
        case 'W':
        {
          if (--colPos < 0)
          {
            std::cout << boundsFail;
            validFlag = false;
          }
          break;
        }
      }
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return validFlag;
  }
}
