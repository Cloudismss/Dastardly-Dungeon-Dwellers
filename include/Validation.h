#ifndef DASTARDLY_DUNGEON_DWELLERS_VALIDATION_H
#define DASTARDLY_DUNGEON_DWELLERS_VALIDATION_H

// Validation Functions
bool validateDecision(int userChoice);
bool validateInput(int userChoice, int rangeLow, int rangeHigh);
bool validateDirection(int rowPos, int colPos, char &userChoice, const int ROWS, const int COLS);

#endif // DASTARDLY_DUNGEON_DWELLERS_VALIDATION_H
