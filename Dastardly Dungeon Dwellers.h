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

// Map Constants - feel free to change - have to both be odd numbers or positioning will be weird
const int MAP_ROWS = 9;
const int MAP_COLUMNS = 9;

// Prototypes

// File Streaming .txt file generator and map generator
void generateCharacterStats(std::ofstream &defaultCharacterStats);
void generateMap(char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition, const int ROW_MIDPOINT, const int COLUMN_MIDPOINT);
void generateMapRoomSpawner(const int ROW_MIDPOINT, const int COLUMN_MIDPOINT, const int ROOM_DISTANCE, const int SIMILAR_DISTANCE, const int ROOMS_ALLOWED, const string &roomName, char roomSymbol, char mapArray[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS]);

// Game Controller
void startGame(std::ifstream &characterStats);

// Map Functions
bool map(char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition);
void mapMovement(int &rowPosition, int &columnPosition);

// Main Menu Group
void mainMenu();
void classSelection(string &className);

// roomController group, these functions are top-level and handle a majority of the game
void roomController(string &className, int &potionCount, int &armorCount, int &goldCount, int &keyCount, int &roomCount, bool &gameOver, bool &gameVictory, char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition, std::ifstream &characterStats);
bool roomEnemy(string &className, int &potionCount, int armorCount, int &goldCount, int &keyCount, int enemyProgression, std::ifstream &characterStats);
bool roomLoot(string &className, int &potionCount, int armorCount, int &goldCount, int &keyCount, int enemyProgression, bool &isEnemyRoom, std::ifstream &characterStats);
void roomMerchant(int &potionCount, int &armorCount, int &goldCount, int &keyCount, const string &className);
void roomMerchantPurchase(int ITEM_INDEX, const string merchantItemName[], const int merchantItemQuantity[], const int merchantItemCost[], int &purchaseAmount, int &goldCount);
void roomExit(int &keyCount, bool &gameVictory);

// battleController group, these functions handle all battle related functions. Called within roomController group
int battleController(const string &className, int &rewardTier, int &potionCount, int armorCount, int enemyProgression, std::ifstream &characterStats);
int battleMenu(string &meleeName, string &magicName, string &rangedName, int playerHealth, int enemyHealth);
void battleHealthArt(int playerHealth, int enemyHealth);
void battleEnemySpawner(int &enemyTier, int &rewardTier, int &enemyHealth, string &enemyName, int enemyProgression, bool &boss);
float playerDamage(int battleMenuSelection, string &meleeName, string &magicName, string &rangedName, const string &className, const string &enemyName, bool boss, std::ifstream &characterStats);
float enemyResistance(const string &abilityName, const string &enemyName, bool boss, int battleMenuSelection);
float enemyDamage(int enemyTier, const string &enemyName, bool boss, int armorCount);
void skillNames(string &skillName, const string &skillType, string &upgradeMessage, const string &className, int tier = 1);
int weaponUpgrade (int checkWeaponUpgrade, int = -1);
int heal(int &potionCount);

// Validation Functions
bool validateDecision(int userChoice);
bool validateInput(int userChoice, int rangeLow, int rangeHigh);
bool validateDirection(int rowPosition, int columnPosition, char &userChoice);

#endif //DASTARDLY_DUNGEON_DWELLERS_DASTARDLY_DUNGEON_DWELLERS_H
