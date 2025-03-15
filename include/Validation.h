#ifndef VALIDATION_H
#define VALIDATION_H

// Input Validation Functions
bool validateDecision(int userChoice);
bool validateInput(int userChoice, int rangeLow, int rangeHigh);
bool validateDirection(int rowPos, int colPos, char &userChoice, const int ROWS, const int COLS);

#endif // VALIDATION_H
