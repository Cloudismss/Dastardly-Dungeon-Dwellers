#ifndef VALIDATION_H
#define VALIDATION_H

// Input Validation Functions
namespace validate
{
  bool decision(int userChoice);
  bool input(int userChoice, int rangeLow, int rangeHigh);
  bool direction(int rowPos, int colPos, char &userChoice, const int ROWS, const int COLS);
}

#endif // VALIDATION_H
