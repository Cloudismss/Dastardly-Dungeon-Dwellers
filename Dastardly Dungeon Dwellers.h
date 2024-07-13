#ifndef DASTARDLY_DUNGEON_DWELLERS_DASTARDLY_DUNGEON_DWELLERS_H
#define DASTARDLY_DUNGEON_DWELLERS_DASTARDLY_DUNGEON_DWELLERS_H

#include <fstream>
#include <iostream>
#include <string>

#include "Main Menu.h"
#include "Map Generator.h"
#include "Room Controller.h"

using std::cin;
using std::cout;
using std::string;

// Prototypes

// File Streaming .txt file generator and map generator
void generateCharacterStats(std::ofstream &defaultCharacterStats);

// Game Controller
void startGame(std::ifstream &characterStats);

#endif //DASTARDLY_DUNGEON_DWELLERS_DASTARDLY_DUNGEON_DWELLERS_H