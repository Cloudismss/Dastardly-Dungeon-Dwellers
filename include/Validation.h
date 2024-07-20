#ifndef DASTARDLY_DUNGEON_DWELLERS_VALIDATION_H
#define DASTARDLY_DUNGEON_DWELLERS_VALIDATION_H

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "Globals.h"

using std::cin;
using std::cout;
using std::setw;
using std::string;

// Validation Functions
bool validateDecision(int userChoice);
bool validateInput(int userChoice, int rangeLow, int rangeHigh);
bool validateDirection(int rowPosition, int columnPosition, char &userChoice, const int MAP_ROWS, const int MAP_COLUMNS);

#endif //DASTARDLY_DUNGEON_DWELLERS_VALIDATION_H