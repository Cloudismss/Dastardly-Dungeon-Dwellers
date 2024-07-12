#ifndef DASTARDLY_DUNGEON_DWELLERS_DASTARDLY_DUNGEON_DWELLERS_H
#define DASTARDLY_DUNGEON_DWELLERS_DASTARDLY_DUNGEON_DWELLERS_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

using std::cout;
using std::cin;
using std::string;
using std::setw;
using std::setfill;
using std::rand;


// Prototypes

// File Streaming .txt file generator and map generator
void generateCharacterStats(std::ofstream &defaultCharacterStats);

// Game Controller
void startGame(std::ifstream &characterStats);

#endif //DASTARDLY_DUNGEON_DWELLERS_DASTARDLY_DUNGEON_DWELLERS_H
