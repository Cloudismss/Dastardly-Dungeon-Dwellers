#ifndef DASTARDLY_DUNGEON_DWELLERS_VALIDATION_H
#define DASTARDLY_DUNGEON_DWELLERS_VALIDATION_H

#include "Globals.h"

// Validation Functions
bool validateDecision(int userChoice);
bool validateInput(int userChoice, int rangeLow, int rangeHigh);
bool validateDirection(int rowPosition, int columnPosition, char &userChoice, const int MAP_ROWS, const int MAP_COLUMNS);

#endif //DASTARDLY_DUNGEON_DWELLERS_VALIDATION_H