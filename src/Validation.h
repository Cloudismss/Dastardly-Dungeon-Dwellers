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
bool validateDirection(int rowPosition, int columnPosition, char &userChoice);