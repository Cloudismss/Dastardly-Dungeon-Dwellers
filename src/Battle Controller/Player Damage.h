#include <fstream>
#include <iostream>
#include <string>

#include "Globals.h"

#include "Art.h"
#include "Enemy Resistance.h"
#include "Skills.h"
#include "Upgrade.h"

using std::cin;
using std::string;

float playerDamage(int battleMenuSelection, string &meleeName, string &magicName, string &rangedName, const string &className, const string &enemyName, bool boss, std::ifstream &characterStats);