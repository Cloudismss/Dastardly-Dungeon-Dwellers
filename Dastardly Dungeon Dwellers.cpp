#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;
using std::setfill;
using std::rand;

// Map Constants - feel free to change - have to both be odd numbers or positioning will be weird
const int MAP_ROWS = 9;
const int MAP_COLUMNS = 9;

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

// Art Functions
void displayMeInABox(const string &message);
void displayMeInABox(const string &message1, const string &message2);
void monologueInABox (const string &message);
void roomEnemyMonologue(int = 0);
void roomLootMonologue(int = 0);
void roomMerchantMonologue(int = 0);
void roomExitMonologue(int = 0);
void tutorialGame();
void tutorialBattle();
void warriorArt();
void mageArt();
void archerArt();
void bardArt();
void treasureArt();
void merchantArt();
void doorArt();
void victoryArt(int roomCount);
void gameOverArt(int roomCount);

const int BASE_MELEE_DAMAGE = 2;
const int BASE_MAGIC_DAMAGE = 2;
const int BASE_RANGED_DAMAGE = 3;
const float BASE_CRIT_CHANCE = 0.10;
const int BASE_ENEMY_DAMAGE = 2;
const int BASE_ENEMY_HEALTH = 5;
const int BOSS_HEALTH = 100;
const int BOSS_DAMAGE_LOW = 8;
const int BOSS_DAMAGE_HIGH = 16;
const int SKILL_UPGRADE = 7;

// Debug toggle - displays useful debug information in the console and gives resources / increased damage
bool debug = false; // Enter -37 at the main menu to enter debug mode

int main()
{
  std::srand(std::time(0)); // NOLINT(*-use-nullptr)

  // I use a rand() here because the first value generated by rand() after srand() seems to be consistently increasing if the rand() bounds are large enough
  rand(); // rand range formula: min + (rand() % ((max + 1) - min))

  // Load Character Stats.txt or create and load Character Stats.txt with defaults, the player can edit the .txt file if they want custom stats
  std::ifstream characterStats;
  characterStats.open("Character Stats.txt");
  if (!characterStats)
  {
    std::ofstream defaultCharacterStats;
    defaultCharacterStats.open("Character Stats.txt");
    generateCharacterStats(defaultCharacterStats);
    defaultCharacterStats.close();
    characterStats.open("Character Stats.txt");
    if (!characterStats)
    {
      std::cerr << "Character Stats.txt failed to open!\n";
      return 0;
    }
  }

  // Main function for the game, runs until the player wins or loses
  startGame(characterStats);

  characterStats.close();

  // Pause the game until the user is ready
  cout << "Press enter to exit the program: ";
  string enterKey = " ";
  getline(cin, enterKey);
  cout << "\n";

  return 0;
}

// Pre-condition: valid output file open
// Post-condition: writes default character stats to created file "Character Stats.txt"
void generateCharacterStats(std::ofstream &defaultCharacterStats)
{
  defaultCharacterStats << "Class Name, Melee Skill | Magic Skill | Ranged Skill | Crit Skill\n"
                        << "\n"
                        << "Warrior, 3 2 2 1.0\n"
                        << "Mage, 1 3 2 3.0\n"
                        << "Archer, 2 2 3 1.0\n"
                        << "Bard, 1 1 1 9.0";
}

// Pre-condition: valid input file open
// Post-condition: runs until the game is over
void startGame(std::ifstream &characterStats)
{
  // Menu Art
  mainMenu();

  // Class selection menu
  string className = " ";
  classSelection(className);

  // These variables will be constantly tracked / updated while the game is played
  int potionCount = 3, armorCount = 0, goldCount = 0, keyCount = 0, roomCount = 0;
  bool gameOver = false, gameVictory = false;

  // DEBUG Option - Extra potions, gold, keys
  if (debug)
  {
    potionCount = 100;
    goldCount = 1000;
    keyCount = 10;
  }

  // These 3 parallel arrays store the player's movements, room cleared status, and room contents
  char mapArray[MAP_ROWS][MAP_COLUMNS];
  bool roomExplored[MAP_ROWS][MAP_COLUMNS];
  string roomContents[MAP_ROWS][MAP_COLUMNS];

  // Constants to hold midpoints
  const int ROW_MIDPOINT = MAP_ROWS / 2;
  const int COLUMN_MIDPOINT = MAP_COLUMNS / 2;

  // These 3 pointers are initialized to the middle of the array
  char *playerPosition = &mapArray[ROW_MIDPOINT][COLUMN_MIDPOINT];
  bool *exploredPosition = &roomExplored[ROW_MIDPOINT][COLUMN_MIDPOINT];
  string *contentsPosition = &roomContents[ROW_MIDPOINT][COLUMN_MIDPOINT];

  // Generates the map with rooms to traverse
  generateMap(mapArray, roomExplored, roomContents, playerPosition, exploredPosition, contentsPosition, ROW_MIDPOINT, COLUMN_MIDPOINT);

  // Runs the game until the player loses all of their health or wins the game
  do
  {
    roomController(className, potionCount, armorCount, goldCount, keyCount, roomCount, gameOver, gameVictory, mapArray, roomExplored, roomContents, playerPosition, exploredPosition, contentsPosition, characterStats);
  } while (!gameOver && !gameVictory);

  if (gameVictory)
  {
    victoryArt(roomCount);
  }
  if (gameOver)
  {
    gameOverArt(roomCount);
  }
}

// Pre-condition: called by startGame()
// Post-condition: displays a menu with options to start the game or read the tutorial
void mainMenu()
{
  bool loopFlag = true;
  do
  {
    cout << ".-------------------------------------------------------------.\n"
            "|                                                             |\n"
            "|     ____    _    ____ _____  _    ____  ____  _  __   __    |\n"
            "|    |  _ \\  / \\  / ___|_   _|/ \\  |  _ \\|  _ \\| | \\ \\ / /    |\n"
            "|    | | | |/ _ \\ \\___ \\ | | / _ \\ | |_) | | | | |  \\ V /     |\n"
            "|    | |_| / ___ \\ ___) || |/ ___ \\|  _ <| |_| | |___| |      |\n"
            "|    |____/_/   \\_\\____/ |_/_/___\\_\\_|_\\_\\____/|_____|_|      |\n"
            "|    |  _ \\| | | | \\ | |/ ___| ____/ _ \\| \\ | |               |\n"
            "|    | | | | | | |  \\| | |  _|  _|| | | |  \\| |               |\n"
            "|    | |_| | |_| | |\\  | |_| | |__| |_| | |\\  |               |\n"
            "|    |____/_\\___/|_|_\\_|\\____|_____\\___/|_|_\\_|___  ____      |\n"
            "|    |  _ \\ \\      / / ____| |   | |   | ____|  _ \\/ ___|     |\n"
            "|    | | | \\ \\ /\\ / /|  _| | |   | |   |  _| | |_) \\___ \\     |\n"
            "|    | |_| |\\ V  V / | |___| |___| |___| |___|  _ < ___) |    |\n"
            "|    |____/  \\_/\\_/  |_____|_____|_____|_____|_| \\_\\____/     |\n"
            "|                                                             |\n"
            "|                                                             |\n"
            "|            1. Start Game           2. Info                  |\n"
            "|                                                             |\n"
            "'-------------------------------------------------------------'\n";
    int selection = 0;
    cin >> selection;
    if (validateInput(selection, 1, 2))
    {
      if (selection == 1)
      {
        loopFlag = false;
      }
      else if (selection == 2)
      {
        tutorialGame();
        cout << "\n";
      }
    }
    else if (selection == -37) // Secret entry to activate debug mode
    {
      debug = true;
      std::cerr << "Debug mode enabled\n\n";
    }
  } while (loopFlag);
}

// Pre-condition: passed className
// Post-condition: displays class selection menu and stores result in className
void classSelection(string &className)
{
  bool loopFlag = true;
  do
  {
    short int classChoice = 0;
    cout << ".-------------------------------------------------------------.\n"
         << "|                                                             |\n"
         << "|           Please choose a class using numbers 1-3:          |\n"
         << "|                                                             |\n"
         << "|            1. Warrior             Skill: Melee              |\n"
         << "|            2. Mage                Skill: Magic              |\n"
         << "|            3. Archer              Skill: Ranged             |\n"
         << "|                                                             |\n"
         << "'-------------------------------------------------------------'\n";
    cin >> classChoice;
    if (validateInput(classChoice, 1, 999))
    {
      char confirmSelection = ' ';
      bool confirmLoop = true;
      switch (classChoice)
      {
        // Player chose Warrior
        case 1:
        {
          warriorArt();
          do
          {
            cout << "You have selected 'Warrior', continue?\n"
                 << "Y or N: ";
            cin >> confirmSelection;
            if (validateDecision(confirmSelection))
            {
              if (confirmSelection == 'Y' || confirmSelection == 'y')
              {
                className = "Warrior";
                cout << "\nYou've chosen the path of the Warrior\n\n";
                loopFlag = false;
              }
              confirmLoop = false;
            }
          } while (confirmLoop);
          break;
        }

          // Player chose Mage
        case 2:
        {
          mageArt();
          do
          {
            cout << "You have selected 'Mage', continue?\n"
                 << "Y or N: ";
            cin >> confirmSelection;
            if (validateDecision(confirmSelection))
            {
              if (confirmSelection == 'Y' || confirmSelection == 'y')
              {
                className = "Mage";
                cout << "\nYou've chosen the path of the Mage\n\n";
                loopFlag = false;
              }
              confirmLoop = false;
            }
          } while (confirmLoop);
          break;
        }

          // Player chose Archer
        case 3:
        {
          archerArt();
          do
          {
            cout << "You have selected 'Archer', continue?\n"
                 << "Y or N: ";
            cin >> confirmSelection;
            if (validateDecision(confirmSelection))
            {
              if (confirmSelection == 'Y' || confirmSelection == 'y')
              {
                className = "Archer";
                cout << "\nYou've chosen the path of the Archer\n\n";
                loopFlag = false;
              }
              confirmLoop = false;
            }
          } while (confirmLoop);
          break;
        }

          // Player chose an invalid number
        default:
        {
          className = "Bard";
          bardArt();
          cout << "That's wasn't an option >:(\n"
               << "Player has been punished and automatically assigned to class: 'Bard'\n\n";
          loopFlag = false;
          break;
        }
      }
    }
  } while (loopFlag);
}

// Pre-condition: receives mapArray[], roomExplored[], roomContents[], *playerPosition, *exploredPosition, *contentsPosition, and constants from startGame()
// Post-condition: initializes mapArray[] with blanks and roomExplored[] with false, roomContents[] is filled with a random selection of rooms. The spawn room is marked with an '*' in mapArray[] and 'true' in roomExplored[]. If debug is on - mapArray[] is filled with room contents indicators
void generateMap(char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition, const int ROW_MIDPOINT, const int COLUMN_MIDPOINT)
{
  // Initialize all the arrays
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      mapArray[i][j] = ' ';
      roomExplored[i][j] = false;
      roomContents[i][j] = " ";
    }
  }

  // Place the player icon in the starter room and sets the starter room to explored with "start" contents
  *playerPosition = '*';
  *exploredPosition = true;
  *contentsPosition = "Start";

  // Spawn an exit on the map
  const int MIN_EXIT_DISTANCE = 3; // The exit must spawn 3 tiles away from the center
  bool validExitSpawns[MAP_ROWS][MAP_COLUMNS] = {0}; // This array finds a valid spawn location based on distance from spawn
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      if ((i <= ROW_MIDPOINT - MIN_EXIT_DISTANCE || i >= ROW_MIDPOINT + MIN_EXIT_DISTANCE) || (j <= COLUMN_MIDPOINT - MIN_EXIT_DISTANCE || j >= COLUMN_MIDPOINT + MIN_EXIT_DISTANCE))
      {
        validExitSpawns[i][j] = true;
      }
    }
  }
  bool exitPlaced = false;
  do
  {
    int randomRow = rand() % MAP_ROWS;
    int randomColumn = rand() % MAP_COLUMNS;
    if (validExitSpawns[randomRow][randomColumn])
    {
      mapArray[randomRow][randomColumn] = '#';
      roomContents[randomRow][randomColumn] = "Exit";
      exitPlaced = true;
    }
  } while (!exitPlaced);

  // Spawn Merchants
  int merchantDistance = 2; // Merchants must spawn 2 tiles away from the center
  int merchantSimilarDistance = 1; // Merchants rooms must spawn 1 tile away from each other
  int merchantsAllowed = MAP_ROWS / 2 + 1; // Number of merchants to spawn is based on map size
  string merchantName = "Merchant";
  char merchantSymbol = '$';
  generateMapRoomSpawner(ROW_MIDPOINT, COLUMN_MIDPOINT, merchantDistance, merchantSimilarDistance, merchantsAllowed, merchantName, merchantSymbol, mapArray, roomContents);

  // Spawn Remaining Non-Enemy Rooms
  int remainingRoomsDistance = 2; // Non-enemy rooms must spawn 2 tiles away from the center, this is so the first room is guaranteed to contain an enemy
  int remainingRoomsSimilarDistance = 1; // Non-enemy rooms must spawn 1 tiles away from each other
  int remainingRoomsAvailable = (MAP_ROWS * MAP_COLUMNS) - 2 - merchantsAllowed; // The literal 2 is for 1 exit and 1 spawn location

  // Spawn Loot Room
  int lootRoomsAllowed = remainingRoomsAvailable * 0.15f; // 15% of remaining rooms can be loot rooms
  string lootRoomName = "Loot";
  char lootRoomSymbol = 'L';
  generateMapRoomSpawner(ROW_MIDPOINT, COLUMN_MIDPOINT, remainingRoomsDistance, remainingRoomsSimilarDistance, lootRoomsAllowed, lootRoomName, lootRoomSymbol, mapArray, roomContents);

  // Spawn Enemy Rooms
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      if (roomContents[i][j] == " ")
      {
        roomContents[i][j] = "Enemy";
        if (debug)
        {
          mapArray[i][j] = 'E';
        }
      }
    }
  }
}

// Pre-condition: receives mapArray[], roomContents[], and constants from generateMap()
// Post-condition: roomContents[] is filled with a random selection of rooms. If debug is on - mapArray[] is filled with room contents indicators
void generateMapRoomSpawner(const int ROW_MIDPOINT, const int COLUMN_MIDPOINT, const int ROOM_DISTANCE, const int SIMILAR_DISTANCE, const int ROOMS_ALLOWED, const string &roomName, char roomSymbol, char mapArray[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS])
{
  bool validSpawns[MAP_COLUMNS][MAP_COLUMNS] = {0}; // This array finds valid spawn locations based on distance from spawn and other from other spawns in this function
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      // Mark the room as valid if the room is empty and a valid distance away from spawn
      if (roomContents[i][j] == " " && (i <= ROW_MIDPOINT - ROOM_DISTANCE || i >= ROW_MIDPOINT + ROOM_DISTANCE) || (j <= COLUMN_MIDPOINT - ROOM_DISTANCE || j >= COLUMN_MIDPOINT + ROOM_DISTANCE))
      {
        validSpawns[i][j] = true;
      }
    }
  }

  // Using these variable to make sure the function has a way out if it can't find a spawn after x attempts
  int spawnAttempts = 0;
  int allowedAttempts = 10;
  if (roomName == "Merchant")
  {
    allowedAttempts = 100; // I want to ensure the proper amount of merchants are always spawned
  }

  int roomsPlaced = 0;
  do
  {
    // Select a random location
    int randomRow = rand() % MAP_ROWS;
    int randomColumn = rand() % MAP_COLUMNS;

    // Check to make sure the room is valid and empty before spawning the room
    if (validSpawns[randomRow][randomColumn] && roomContents[randomRow][randomColumn] == " ")
    {
      // Place room
      roomContents[randomRow][randomColumn] = roomName;
      validSpawns[randomRow][randomColumn] = false;
      ++roomsPlaced;

      // DEBUG Option - Print loot room icons on map
      if (debug)
      {
        mapArray[randomRow][randomColumn] = roomSymbol;
      }

      // Mark spaces SIMILAR_DISTANCE tile(s) away as invalid spawns, so rooms don't spawn too close to each other - if branches check bounds so I don't assign an out of bounds value
      // TODO num merchants not always correct
      if (randomRow + SIMILAR_DISTANCE < MAP_ROWS)
      {
        validSpawns[randomRow + SIMILAR_DISTANCE][randomColumn] = false;
        if (randomColumn + SIMILAR_DISTANCE < MAP_COLUMNS)
        {
          validSpawns[randomRow + SIMILAR_DISTANCE][randomColumn + SIMILAR_DISTANCE] = false;
        }
        if (randomColumn - SIMILAR_DISTANCE >= 0)
        {
          validSpawns[randomRow + SIMILAR_DISTANCE][randomColumn - SIMILAR_DISTANCE] = false;
        }
      }

      if (randomRow - SIMILAR_DISTANCE >= 0)
      {
        validSpawns[randomRow - SIMILAR_DISTANCE][randomColumn] = false;
        if (randomColumn - SIMILAR_DISTANCE >= 0)
        {
          validSpawns[randomRow - SIMILAR_DISTANCE][randomColumn - SIMILAR_DISTANCE] = false;
        }
        if (randomColumn + SIMILAR_DISTANCE < MAP_COLUMNS)
        {
          validSpawns[randomRow - SIMILAR_DISTANCE][randomColumn + SIMILAR_DISTANCE] = false;
        }
      }

      if (randomColumn + SIMILAR_DISTANCE < MAP_COLUMNS)
      {
        validSpawns[randomRow][randomColumn + SIMILAR_DISTANCE] = false;
      }
      if (randomColumn - SIMILAR_DISTANCE >= 0)
      {
        validSpawns[randomRow][randomColumn - SIMILAR_DISTANCE] = false;
      }
    }

    // Fallback exit if the spawning luck is poor
    else
    {
      ++spawnAttempts;
    }
  } while (roomsPlaced < ROOMS_ALLOWED && spawnAttempts < allowedAttempts);
}

// Pre-condition: called by startGame() in a loop, passed className, inventory variables, game win/lose variables, map arrays and pointers, and characterStats file stream
// Post-condition: a room is selected within roomController, and game win/lose variables are updated based on result of room. The game ends if the game is won or lost
void roomController(string &className, int &potionCount, int &armorCount, int &goldCount, int &keyCount, int &roomCount, bool &gameOver, bool &gameVictory, char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition, std::ifstream &characterStats)
{
  static int enemyProgression;
  // map() allows the player to move between rooms. It returns false if the room has not been explored yet
  if (!(map(mapArray, roomExplored, roomContents, playerPosition, exploredPosition, contentsPosition)))
  {
    if (*contentsPosition == "Enemy")
    {
      roomEnemyMonologue();
      if (!roomEnemy(className, potionCount, armorCount, goldCount, keyCount, roomCount, characterStats))
      {
        gameOver = true;
        return;
      }
      ++roomCount;
      ++enemyProgression;
    }
    else if (*contentsPosition == "Loot")
    {
      bool isEnemyRoom = false;
      roomLootMonologue();
      treasureArt();
      if(!roomLoot(className, potionCount, armorCount, goldCount, keyCount, roomCount, isEnemyRoom, characterStats))
      {
        gameOver = true;
        return;
      }
      ++roomCount;
      if (isEnemyRoom)
      {
        ++enemyProgression;
      }
    }
    else if (*contentsPosition == "Merchant")
    {
      roomMerchantMonologue();
      merchantArt();
      roomMerchant(potionCount, armorCount, goldCount, keyCount, className);
      ++roomCount;
    }
    else if (*contentsPosition == "Exit")
    {
      roomExitMonologue();
      roomExit(keyCount, gameVictory);
      ++roomCount;
    }
  }

  // This branch runs if the room has already been explored
  else
  {
    // Set dialogue switch to -1, so it runs room cleared dialogue
    int dialogueSwitch = -1;
    if (*contentsPosition == "Enemy")
    {
      monologueInABox("A powerful foe once inhabited this room");
      if (1 + (rand() % 100) <= 50)
      {
        roomEnemyMonologue(dialogueSwitch);
        if (!roomEnemy(className, potionCount, armorCount, goldCount, keyCount, roomCount, characterStats))
        {
          gameOver = true;
          return;
        }
        ++enemyProgression;
      }
    }
    else if (*contentsPosition == "Loot")
    {
      monologueInABox("A chest used to sit before me in this room");
      if (1 + (rand() % 100) <= 50)
      {
        roomLootMonologue(dialogueSwitch);
        if (!roomEnemy(className, potionCount, armorCount, goldCount, keyCount, roomCount, characterStats))
        {
          gameOver = true;
          return;
        }
        ++enemyProgression;
      }
    }
    else if (*contentsPosition == "Merchant")
    {
      monologueInABox("A friendly traveling merchant resides here");
      roomMerchantMonologue(dialogueSwitch);
      merchantArt();
      roomMerchant(potionCount, armorCount, goldCount, keyCount, className);
    }
    else if (*contentsPosition == "Exit")
    {
      monologueInABox("A strange sensation controls my actions");
      roomExitMonologue(dialogueSwitch);
      roomExit(keyCount, gameVictory);
    }
    else if (*contentsPosition == "Start")
    {
      monologueInABox("This room seems familiar... have I gone in a circle???");
    }
  }

  // Display text indicating the enemy spawner has become more challenging
  static bool sayOnce1 = false, sayOnce2 = true, sayOnce3 = true;
  if (enemyProgression == 5)
  {
    if (!sayOnce1)
    {
      monologueInABox("Stronger foes have emerged from the depths of the dungeon...");
      sayOnce1 = true;
      sayOnce2 = false;
    }
  }
  if (enemyProgression == 10)
  {
    if (!sayOnce2)
    {
      monologueInABox("Stronger foes have emerged from the depths of the dungeon...");
      sayOnce2 = true;
      sayOnce3 = false;
    }
  }
  if (enemyProgression == 15)
  {
    if (!sayOnce3)
    {
      monologueInABox("Stronger foes have emerged from the depths of the dungeon...");
      sayOnce3 = true;
    }
  }
}

// Pre-condition: called by roomController(), passed mapArray[], roomExplored[], roomContents[], array pointers
// Post-condition: Returns true if the room has already been explored. Allows the player to move around the map. Updates mapArray[] with current and previous player position. Updates roomExplored[] with true once a new room is entered
bool map(char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition)
{
  // Position Tracking Variables
  static int rowPosition = MAP_ROWS / 2, columnPosition = MAP_COLUMNS / 2;
  static char *previousPlayerPosition = &mapArray[MAP_ROWS / 2][MAP_COLUMNS / 2];

  // Prints the map
  cout << setfill('-') << setw(64) << " " << setfill(' ');
  cout << "\n\n";
  cout << "MAP SELECTION" << "\n\n";
  cout << "You are here [*]\n";
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      cout << "[" << mapArray[i][j] << "]" ;
    }
    cout << "\n";
  }

  // DEBUG OPTION - prints other array maps
  if (debug)
  {
    cout << "\n";
    cout << setfill('-') << setw(64) << " " << setfill(' ');
    cout << "\n\n";
    cout << setw(65/2) << "DEBUG MAPS" << "\n\n";
    for (int i = 0; i < MAP_ROWS; ++i)
    {
      for (int j = 0; j < MAP_COLUMNS; ++j)
      {
        cout << "[" << roomExplored[i][j] << "]" ;
      }
      cout << "\n";
    }
    cout << "\n";
    for (int i = 0; i < MAP_ROWS; ++i)
    {
      for (int j = 0; j < MAP_COLUMNS; ++j)
      {
        cout << "[" << roomContents[i][j] << "]" ;
      }
      cout << "\n";
    }
    cout << "\n" << setfill('-') << setw(64) << " " << setfill(' ');
    cout << "\n";
  }
  cout << "\n";

  // Adjusts either rowPosition or columnPosition by 1 or -1 based on direction choice by the user
  mapMovement(rowPosition, columnPosition);

  // Move the pointers to new positions based on direction choice by the user
  playerPosition = &mapArray[rowPosition][columnPosition];
  exploredPosition = &roomExplored[rowPosition][columnPosition];

  // Check if we've been in this room before
  bool roomCleared = false;
  if (*exploredPosition)
  {
    roomCleared = true;
  }
  else
  {
    // Set the current index to true, since we'll be clearing this room next
    *exploredPosition = true;
  }

  // Place new value in previousPlayerPosition
  if (!(*contentsPosition == "Merchant" || *contentsPosition == "Exit"))
  {
    *previousPlayerPosition = 'o'; // Place a 'o' value in previousPlayerPosition pointer's element to indicate a previously cleared room
  }
  else if (*contentsPosition == "Merchant")
  {
    *previousPlayerPosition = '$'; // Place a '$' value in previousPlayerPosition pointer's element to indicate a discovered merchant shop
  }
  else if (*contentsPosition == "Exit")
  {
    *previousPlayerPosition = '#'; // Place a '#' value in previousPlayerPosition pointer's element to indicate the exit
  }

  // Moving this pointer last out of the bunch, so previousPlayerPosition can read its value before contentsPosition moves
  contentsPosition = &roomContents[rowPosition][columnPosition];

  // Place new value in playerPosition
  *playerPosition = '*'; // Place an asterisk value in playerPosition pointer's element

  // Set previousPlayerPosition to playerPosition, to record the last movement
  previousPlayerPosition = playerPosition;

  // Prints the map
  cout << "You are here [*]\n";
  for (int i = 0; i < MAP_ROWS; ++i)
  {
    for (int j = 0; j < MAP_COLUMNS; ++j)
    {
      cout << "[" << mapArray[i][j] << "]" ;
    }
    cout << "\n";
  }
  cout << "\n";
  cout << setfill('-') << setw(64) << " " << setfill(' ') << "\n\n";

  // If the room was already visited, return true, if not, return false
  if (roomCleared)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Pre-condition: called by map(), passed rowPosition and columnPosition
// Post-condition: updates both variables based on user selection
void mapMovement(int &rowPosition, int &columnPosition)
{
  bool loopFlag = true;
  char directionChoice = ' ';
  do
  {
    // Accept direction from user, validates that the direction is within map bounds
    cout << "Which direction would you like to go? (N|E|S|W): ";
    cin >> directionChoice;
    cout << "\n";
    if (validateDirection(rowPosition, columnPosition, directionChoice))
    {
      loopFlag = false;
    }
  } while (loopFlag);

  // Adjust row and column values based on user choice
  switch (directionChoice)
  {
    case 'N':
    {
      --rowPosition;
      break;
    }
    case 'S':
    {
      ++rowPosition;
      break;
    }
    case 'E':
    {
      ++columnPosition;
      break;
    }
    case 'W':
    {
      --columnPosition;
      break;
    }
  }
}

// Pre-condition: called by roomController(), passed enemyProgression, inventory variables and className / characterStats
// Post-condition: Returns true if the player survives the room, updates inventory variables based on result
bool roomEnemy(string &className, int &potionCount, int armorCount, int &goldCount, int &keyCount, int enemyProgression, std::ifstream &characterStats)
{
  // Run the battleController function. It returns 1 if the player wins the battle, -1 if the player successfully runs away, and 0 if they lose.
  int rewardTier = 1;
  int battleResult = battleController(className, rewardTier, potionCount, armorCount, enemyProgression, characterStats);

  // Control variable that enables the pause screen after winning the battle
  bool battleSuccess = false;

  // Player won the battle
  if (battleResult == 1)
  {
    battleSuccess = true;

    cout << "You check the enemy for valuables:\n";
    int lootRoll = 1 + (rand() % 100);

    if (rewardTier == 1)
    {
      // 10% chance to earn a potion
      if (lootRoll <= 10)
      {
        ++potionCount;
        cout << "Potion added\n";
      }

      // 85% chance to earn a random amount of gold
      if (lootRoll <= 85)
      {
        // Amount of gold returned is between 5-15
        int goldAdded = 5 + (rand() % 11);
        goldCount += goldAdded;
        cout << "Gold x" << goldAdded << " added\n";
      }

      // Nothing found
      if (lootRoll > 85)
      {
        cout << "You found nothing of value\n";
      }
    }

    else if (rewardTier == 2)
    {
      // 30% chance to earn a potion
      if (lootRoll <= 30)
      {
        ++potionCount;
        cout << "Potion added\n";
      }

      // 90% chance to earn a random amount of gold
      if (lootRoll <= 90)
      {
        // Amount of gold returned is between 5-20
        int goldAdded = 5 + (rand() % 16);
        goldCount += goldAdded;
        cout << "Gold x" << goldAdded << " added\n";
      }

      // Nothing found
      if (lootRoll > 90)
      {
        cout << "You found nothing of value\n";
      }
    }

    else if (rewardTier == 3)
    {
      // 60% chance to earn a potion(s)
      if (lootRoll <= 60)
      {
        int potionAdded = 1 + (rand() % 2);
        potionCount += potionAdded;
        if (potionAdded == 1)
        {
          cout << "Potion added\n";
        }
        else
        {
          cout << "Potion x" << potionAdded << " added\n";
        }
      }

      // 100% chance to earn a random amount of gold between 10-20
      int goldAdded = 10 + (rand() % 11);
      goldCount += goldAdded;
      cout << "Gold x" << goldAdded << " added\n";
    }

    else if (rewardTier == 4)
    {
      // 90% chance to earn a potion(s)
      if (lootRoll <= 90)
      {
        int potionAdded = 1 + (rand() % 2);
        potionCount += potionAdded;
        if (potionAdded == 1)
        {
          cout << "Potion added\n";
        }
        else
        {
          cout << "Potion x" << potionAdded << " added\n";
        }
      }

      // 100% chance to earn a random amount of gold between 15-20
      int goldAdded = 15 + (rand() % 6);
      goldCount += goldAdded;
      cout << "Gold x" << goldAdded << " added\n";

      // 5% chance to earn the golden key
      if (lootRoll <= 5)
      {
        ++keyCount;
        cout << "\n";
        displayMeInABox("GOLDEN KEY Acquired!");
      }
    }

    else if (rewardTier == 5)
    {
      // 100% chance to earn a potion(s)
      int potionAdded = 1 + (rand() % 2);
      potionCount += potionAdded;
      cout << "Potion x" << potionAdded << " added\n";

      // 100% chance to earn a random amount of gold between 15-20
      int goldAdded = 15 + (rand() % 6);
      goldCount += goldAdded;
      cout << "Gold x" << goldAdded << " added\n";

      // 15% chance to earn the golden key
      if (lootRoll <= 15)
      {
        ++keyCount;
        cout << "\n";
        displayMeInABox("GOLDEN KEY Acquired!");
      }
    }

    else if (rewardTier == 10)
    {
      // 100% chance to earn 5-10 potions
      int potionAdded = 5 + (rand() % 6);
      potionCount += potionAdded;
      cout << "Potion x" << potionAdded << " added\n";

      // 100% chance to earn a random amount of gold between 25-50
      int goldAdded = 25 + (rand() % 26);
      goldCount += goldAdded;
      cout << "Gold x" << goldAdded << " added\n";

      // 100% chance to earn the golden key
      ++keyCount;
      cout << "\n";
      displayMeInABox("GOLDEN KEY Acquired!");
    }
    cout << "\n";
  }

  // Player successfully ran away
  else if (battleResult == -1)
  {
    battleSuccess = true;
  }

  // This check ensures the player isn't asked for the next room after they lose
  if (battleSuccess)
  {
    // Pause the game until the user is ready
    cout << "Press enter to continue to the next room: ";
    string enterKey = " ";
    getline(cin, enterKey);
    cout << "\n";
  }

  // If battleSuccess is false, end the program
  return battleSuccess;
}

// Pre-condition: called by roomController(), passed enemyProgression, isEnemyRoom, inventory variables and className / characterStats
// Post-condition: Returns true if the player survives the room, updates inventory variables based on result, isEnemyRoom is updated to true if an enemy is spawned
bool roomLoot(string &className, int &potionCount, int armorCount, int &goldCount, int &keyCount, int enemyProgression, bool &isEnemyRoom, std::ifstream &characterStats)
{
  // This room could be a trap, ask the player if they want to attempt to loot the chest
  bool lootSuccess = false;
  bool loopFlag = true;
  char chestSelection = ' ';
  do
  {
    cout << "Do you look inside?\n"
         << "Y or N:";
    cin >> chestSelection;
    if (validateDecision(chestSelection))
    {
      loopFlag = false;
    }
  } while (loopFlag);

  // Player wants to open the chest
  if (chestSelection == 'Y' || chestSelection == 'y')
  {
    cout << "\nYou carefully lift the lid open";

    // There is a 90% chance the room isn't a trap
    if (1 + (rand() % 100) <= 90)
    {
      cout << " and found the following items:\n";

      // Player is guaranteed a random amount of gold between 15-30
      int goldAdded = 15 + (rand() % 16);
      goldCount += goldAdded;
      cout << "Gold x" << goldAdded << " added\n";

      int lootRoll = 1 + (rand() % 100);

      // 75% chance the player is given potion(s)
      if (lootRoll <= 75)
      {
        // Player is given a random amount of potions between 2-3
        int potionAdded = 2 + (rand() % 2);
        potionCount += potionAdded;
        if (potionAdded > 1)
        {
          cout << "Potion x" << potionAdded << " added\n";
        }
        else
        {
          cout << "Potion added\n";
        }
      }
      cout << "\n";

      // 30% chance the player is given the golden key
      if (lootRoll <= 30)
      {
        ++keyCount;
        displayMeInABox("GOLDEN KEY Acquired!");
      }

      // Player successfully cleared the room
      lootSuccess = true;

      // Pause the game until the user is ready
      cout << "Press enter to continue to the next room: ";
      string enterKey = " ";
      getline(cin, enterKey);
      cout << "\n";
    }

    // There is a 10% chance the room is a trap
    else
    {
      cout << " but it's empty!\n"
           << "You quickly slam the lid closed as you hear the door in front of you crack open!\n\n";

      // Run roomEnemy, Returns true if the player wins the battle
      if (roomEnemy(className, potionCount, armorCount, goldCount, keyCount, enemyProgression, characterStats))
      {
        lootSuccess = true;
        isEnemyRoom = true;
      }
    }
  }

  // Player chose not to open the chest
  else
  {
    cout << "\nYou sense this may be a trap, and quickly exit the room\n\n";
    lootSuccess = true;

    // Pause the game until the user is ready
    cout << "Press enter to continue to the next room: ";
    string enterKey = " ";
    getline(cin, enterKey);
    cout << "\n";
  }

  // If a battle is triggered and lost, a false value will end the program
  return lootSuccess;
}

// Pre-condition: called by roomController(), passed inventory variables and className
// Post-condition: Runs merchant shop loop until the player leaves, updates inventory variables
void roomMerchant(int &potionCount, int &armorCount, int &goldCount, int &keyCount, const string &className)
{
  // Initialize Merchant Shop arrays
  const int NUM_ITEMS = 7 + 1; // Adding one here so the visual menu matches index location, we're not using index 0. (Wasteful, but it really helped me visualize the shop output) - Refactor
  int merchantItemQuantity[NUM_ITEMS] = {0};
  int merchantItemCost[NUM_ITEMS] = {0};
  string merchantItemName[NUM_ITEMS];
  for (int i = 0; i < NUM_ITEMS; ++i)
  {
    merchantItemName[i] = " ";
  }

  // shopItemIndex array variable is used only to aid in translating user input indexes to 1-6 in numberTranslated loop. We need this since the shop is randomized
  int shopItemIndex[NUM_ITEMS] = {0};
  for (int i = 1; i < NUM_ITEMS; ++i)
  {
    shopItemIndex[i] = i;
  }

  // Upgrade variables
  const int MELEE_WEAPON = 0, MAGIC_WEAPON = 1, RANGED_WEAPON = 2;
  const int KEY_CHANCE = 75;
  const int UPGRADE_CHANCE = 60;
  const int UPGRADE_COST = 50;
  int meleeChance = 1 + rand() % 100;
  int magicChance = 1 + rand() % 100;
  int rangedChance = 1 + rand() % 100;
  int goldenKeyChance = 1 + rand() % 100;

  // Slot 1 - The Merchant has a random number of potions between 2-5
  const int POTION_INDEX = 1;
  merchantItemName[POTION_INDEX] = "Potion";
  merchantItemQuantity[POTION_INDEX] = 2 + (rand() % 4);
  merchantItemCost[POTION_INDEX] = 15;

  // Slot 2 - The Merchant has a random number of armor platings between 1-3
  const int ARMOR_UPGRADE_INDEX = 2;
  merchantItemName[ARMOR_UPGRADE_INDEX] = "Armor Plating";
  merchantItemQuantity[ARMOR_UPGRADE_INDEX] = 1 + (rand() % 3);
  merchantItemCost[ARMOR_UPGRADE_INDEX] = 30;

  // Slot 3 - Melee Upgrade
  const int MELEE_UPGRADE_INDEX = 3;
  if (className == "Warrior")
  {
    merchantItemName[MELEE_UPGRADE_INDEX] = "Sword Sharpening";
  }
  else if (className == "Mage")
  {
    merchantItemName[MELEE_UPGRADE_INDEX] = "Staff Density";
  }
  else if (className == "Archer")
  {
    merchantItemName[MELEE_UPGRADE_INDEX] = "Honed Blades";
  }
  else if (className == "Bard")
  {
    merchantItemName[MELEE_UPGRADE_INDEX] = "Lute Polish";
  }
  merchantItemQuantity[MELEE_UPGRADE_INDEX] = 0;
  merchantItemCost[MELEE_UPGRADE_INDEX] = UPGRADE_COST;

  // Slot 4 - Staff Upgrade
  const int MAGIC_UPGRADE_INDEX = 4;
  if (className == "Warrior")
  {
    merchantItemName[MAGIC_UPGRADE_INDEX] = "Shield Polish";
  }
  else if (className == "Mage")
  {
    merchantItemName[MAGIC_UPGRADE_INDEX] = "Runald's Ice Band";
  }
  else if (className == "Archer")
  {
    merchantItemName[MAGIC_UPGRADE_INDEX] = "Toxic Canister";
  }
  else if (className == "Bard")
  {
    merchantItemName[MAGIC_UPGRADE_INDEX] = "Throat Lubricant";
  }
  merchantItemQuantity[MAGIC_UPGRADE_INDEX] = 0;
  merchantItemCost[MAGIC_UPGRADE_INDEX] = UPGRADE_COST;

  // Slot 5 - Arrow Upgrade
  const int RANGED_UPGRADE_INDEX = 5;
  if (className == "Warrior")
  {
    merchantItemName[RANGED_UPGRADE_INDEX] = "Titanium Throwing Sleeve";
  }
  else if (className == "Mage")
  {
    merchantItemName[RANGED_UPGRADE_INDEX] = "Static Cleanse";
  }
  else if (className == "Archer")
  {
    merchantItemName[RANGED_UPGRADE_INDEX] = "Arcane Arrow Treatment";
  }
  else if (className == "Bard")
  {
    merchantItemName[RANGED_UPGRADE_INDEX] = "Chapstick";
  }
  merchantItemQuantity[RANGED_UPGRADE_INDEX] = 0;
  merchantItemCost[RANGED_UPGRADE_INDEX] = UPGRADE_COST;

  // Slot 6 - Golden Key
  const int GOLDEN_KEY_INDEX = NUM_ITEMS - 2;
  merchantItemName[GOLDEN_KEY_INDEX] = "Golden Key";
  merchantItemQuantity[GOLDEN_KEY_INDEX] = 0;
  merchantItemCost[GOLDEN_KEY_INDEX] = 100;

  // Slot 7 - Exit Index
  const int EXIT_INDEX = NUM_ITEMS - 1;
  merchantItemName[EXIT_INDEX] = "Exit";
  merchantItemQuantity[EXIT_INDEX] = 1;

  // Shop position tracking array, only used for translating positions in switch statement
  string shopItemOrder[NUM_ITEMS];
  for (int i = 0; i < NUM_ITEMS; ++i)
  {
    shopItemOrder[i] = " ";
  }

  // Chance to sell melee upgrade
  if (meleeChance <= UPGRADE_CHANCE)
  {
    merchantItemQuantity[MELEE_UPGRADE_INDEX] = 1;
  }

  // Chance to sell magic upgrade
  if (magicChance <= UPGRADE_CHANCE)
  {
    merchantItemQuantity[MAGIC_UPGRADE_INDEX] = 1;
  }

  // Chance to sell ranged upgrade
  if (rangedChance <= UPGRADE_CHANCE)
  {
    merchantItemQuantity[RANGED_UPGRADE_INDEX] = 1;
  }

  // Chance to sell golden key
  if (goldenKeyChance <= KEY_CHANCE)
  {
    merchantItemQuantity[GOLDEN_KEY_INDEX] = 1;
  }

  // Loop the shop until the player is ready to leave
  bool shopLoop = true;
  do
  {
    // Display Top Box of Merchant Shop
    string goldDisplay = "Gold: ";
    goldDisplay += std::to_string(goldCount);
    string potionDisplay = "Potions: ";
    potionDisplay += std::to_string(potionCount);
    cout << "." << setfill('-') << setw(63) << ".\n";
    cout << "|" << setfill(' ') << setw(2) << " " << goldDisplay << setw(57 - goldDisplay.length()) << potionDisplay << setw(2) << " " << "|\n";
    cout << "|" << setfill(' ') << setw(63) << "|\n";

    // Counter to hold amount of items/lines to be displayed
    int shopItemCount = 0;

    // Display middle rows - randomized shop items
    for (int i = 1; i < NUM_ITEMS; ++i)
    {
      // Print all shop items except for exit
      if (i < EXIT_INDEX)
      {
        // Only list items that are for sale
        if (merchantItemQuantity[i] > 0)
        {
          // Only print the quantity if there are more than one
          if (merchantItemQuantity[i] > 1)
          {
            cout << "|" << setw(10) << " " << ++shopItemCount << ". " << merchantItemName[i] << "(s) x" << merchantItemQuantity[i]
                 << setw(24 - merchantItemName[i].length()) << " " << "Cost: " << merchantItemCost[i] << setw(14 - std::to_string(merchantItemCost[i]).size()) << "|\n";
          }
          // Don't print the quantity if there's only one
          else if (merchantItemQuantity[i] == 1)
          {
            cout << "|" << setw(10) << " " << ++shopItemCount << ". " << merchantItemName[i]
                 << setw(30 - merchantItemName[i].length()) << " " << "Cost: " << merchantItemCost[i] << setw(14 - std::to_string(merchantItemCost[i]).size()) << "|\n";
          }
          // Places item name values in shopItemOrder array
          shopItemOrder[shopItemCount] = merchantItemName[i];
        }
      }
      // Prints the exit
      else if (i == EXIT_INDEX)
      {
       cout << "|" << setw(10) << " " << ++shopItemCount << ". Exit" << setw(46) << "|\n";
       // Places item name values in shopItemOrder array
       shopItemOrder[shopItemCount] = merchantItemName[i];
      }
    }

    // Display Bottom Box of Merchant Shop
    cout << "|" << setw(63) << "|\n"
         << "'" << setfill('-') << setw(63) << "'\n"
         << "\n" << setfill(' ');

    // Validate Selection
    int userShopSelection = 0;
    bool loopFlag = true;
    do
    {
      cout << "\tWhat would you like to purchase? ";
      cin >> userShopSelection;
      cout << "\n";
      if (validateInput(userShopSelection, 1, shopItemCount))
      {
        loopFlag = false;
      }
    } while (loopFlag);

    // Translate userShopSelection to a value matching original indexes 1-6 for usage in switch statement
    bool numberTranslated = false;
    int loopCount = 1;
    do
    {
      if (shopItemOrder[userShopSelection] == merchantItemName[loopCount])
      {
        userShopSelection = shopItemIndex[loopCount];
        numberTranslated = true;
      }
      ++loopCount;
    } while (!numberTranslated);

    // Switch player purchase choice
    int purchaseAmount = 0;
    switch (userShopSelection)
    {
      // Player chose to buy potions
      case POTION_INDEX:
      {
        roomMerchantPurchase(POTION_INDEX, merchantItemName, merchantItemQuantity, merchantItemCost, purchaseAmount,goldCount);
        if (purchaseAmount > 0)
        {
          merchantItemQuantity[POTION_INDEX] -= purchaseAmount;
          goldCount -= merchantItemCost[POTION_INDEX] * purchaseAmount;
          potionCount += purchaseAmount;
        }
        break;
      }

      // Player chose to buy armor upgrades
      case ARMOR_UPGRADE_INDEX:
      {
        roomMerchantPurchase(ARMOR_UPGRADE_INDEX, merchantItemName, merchantItemQuantity, merchantItemCost, purchaseAmount,goldCount);
        if (purchaseAmount > 0)
        {
          merchantItemQuantity[ARMOR_UPGRADE_INDEX] -= purchaseAmount;
          goldCount -= merchantItemCost[ARMOR_UPGRADE_INDEX] * purchaseAmount;
          armorCount += purchaseAmount;
        }
        break;
      }

      // Player chose to buy the sword upgrade
      case MELEE_UPGRADE_INDEX:
      {
        roomMerchantPurchase(MELEE_UPGRADE_INDEX, merchantItemName, merchantItemQuantity, merchantItemCost, purchaseAmount, goldCount);
        if (purchaseAmount > 0)
        {
          if (className == "Warrior")
          {
            cout << "\tYou feel an immense power emanating from your blade\n";
          }
          else if (className == "Mage")
          {
            cout << "\tThe weight of a distant star infuses within your staff\n";
          }
          else if (className == "Archer")
          {
            cout << "\tYour blades shimmer a soft blue gleam, there may be enemies nearby\n";
          }
          else if (className == "Bard")
          {
            cout << "\tYour lute gently tugs on your shoulder, politely yearning for your affection\n";
          }
          cout <<  "\tYour melee damage has been upgraded!\n\n";
          merchantItemQuantity[MELEE_UPGRADE_INDEX] -= purchaseAmount;
          goldCount -= merchantItemCost[MELEE_UPGRADE_INDEX] * purchaseAmount;
          weaponUpgrade(0, MELEE_WEAPON);
        }
        break;
      }

      // Player chose to buy the magic upgrade
      case MAGIC_UPGRADE_INDEX:
      {
        roomMerchantPurchase(MAGIC_UPGRADE_INDEX, merchantItemName, merchantItemQuantity, merchantItemCost, purchaseAmount, goldCount);
        if (purchaseAmount > 0)
        {
          if (className == "Warrior")
          {
            cout << "\tYour shield shakes with vicious ferocity, it is ready to bash your foes\n";
          }
          else if (className == "Mage")
          {
            cout << "\tA soft implosion pops within your staff, you feel empowered by the spirits of the dungeon\n";
          }
          else if (className == "Archer")
          {
            cout << "\tYour toxins breathe a voracious pestilence, suffocating your enemies\n";
          }
          else if (className == "Bard")
          {
            cout << "\tYour throat feels nice and refreshed\n";
          }
          cout <<  "\tYour magic damage has been upgraded!\n\n";
          merchantItemQuantity[MAGIC_UPGRADE_INDEX] -= purchaseAmount;
          goldCount -= merchantItemCost[MAGIC_UPGRADE_INDEX] * purchaseAmount;
          weaponUpgrade(0, MAGIC_WEAPON);
        }
        break;
      }

      // Player chose to buy the ranged upgrade
      case RANGED_UPGRADE_INDEX:
      {
        roomMerchantPurchase(RANGED_UPGRADE_INDEX, merchantItemName, merchantItemQuantity, merchantItemCost, purchaseAmount, goldCount);
        if (purchaseAmount > 0)
        {
          if (className == "Warrior")
          {
            cout << "\tYour spear calls for your grasp, ready to soar with reckless ferocity\n";
          }
          else if (className == "Mage")
          {
            cout << "\tA mystical cloud descends upon you, relieving you of your static charge\n";
          }
          else if (className == "Archer")
          {
            cout << "\tYour quiver shakes ferociously, you knock your bow with fearless determination\n";
          }
          else if (className == "Bard")
          {
            cout << "\tThe air in this dungeon is very dry, you'll certainly need this\n";
          }
          cout <<  "\tYour ranged damage has been upgraded!\n\n";
          merchantItemQuantity[RANGED_UPGRADE_INDEX] -= purchaseAmount;
          goldCount -= merchantItemCost[RANGED_UPGRADE_INDEX] * purchaseAmount;
          weaponUpgrade(0, RANGED_WEAPON);
        }
        break;
      }

      // Player chose to purchase the golden key
      case GOLDEN_KEY_INDEX:
      {
        // Make sure the player has enough gold
        if (goldCount >= merchantItemCost[GOLDEN_KEY_INDEX])
        {
          // Validate selection
          char selection = ' ';
          loopFlag = true;
          do
          {
            cout << "\tWould you like to buy the golden key for " << merchantItemCost[GOLDEN_KEY_INDEX] << " gold?\n";
            cout << "\tY or N: ";
            cin >> selection;
            cout << "\n";
            if (validateDecision(selection))
            {
              loopFlag = false;
            }
          } while (loopFlag);

          // Player chose to purchase the golden key
          if (selection == 'Y' || selection == 'y')
          {
            merchantItemQuantity[GOLDEN_KEY_INDEX] -= 1;
            goldCount -= merchantItemCost[GOLDEN_KEY_INDEX];
            ++keyCount;
            cout << "\t." << setfill('-') << setw(46) << ".\n"
                 << "\t|" << setfill(' ') << setw(46) << "|\n"
                 << "\t|" << setw(12) << " " << "GOLDEN KEY acquired!" << setw(11) << " " << " |\n"
                 << "\t|" << setfill(' ') << setw(46) << "|\n"
                 << "\t'" << setfill('-') << setw(46) << "'\n"
                 << "\n";
          }
        }

        // Player doesn't have enough gold
        else
        {
          cout << "\tYou don't have enough gold!\n\n";
        }
        break;
      }

      // Player chose to leave
      case EXIT_INDEX:
      {
        cout << "\tGoodbye!\n\n";
        shopLoop = false;
        break;
      }
    }
  } while (shopLoop);

  // Pause the game until the user is ready
  cout << "Press enter to continue to the next room: ";
  string enterKey = " ";
  getline(cin, enterKey);
  cout << "\n";
}

// Pre-condition: called by roomMerchant(), passed item array and item information, along with inventory variables
// Post-condition: asks how many of the item the player would like to buy, checks goldCount to validate purchase, updates purchaseAmount for usage in roomMerchant()
void roomMerchantPurchase(int ITEM_INDEX, const string merchantItemName[], const int merchantItemQuantity[], const int merchantItemCost[], int &purchaseAmount, int &goldCount)
{
  // Validate purchase amount
  bool loopFlag = true;

  // Selected item has >1 qty
  if (merchantItemQuantity[ITEM_INDEX] > 1)
  {
    do
    {
      // Ask the player how many items they'd like to buy
      cout << "\t" << merchantItemName[ITEM_INDEX] << "(s) available: " << merchantItemQuantity[ITEM_INDEX] << "\n";
      cout << "\tHow many " << merchantItemName[ITEM_INDEX] << "(s) would you like to buy?: ";
      cin >> purchaseAmount;
      cout << "\n";
      if (validateInput(purchaseAmount, 0, merchantItemQuantity[ITEM_INDEX]))
      {
        loopFlag = false;

        // If they choose 0, exit purchase menu
        if (purchaseAmount == 0)
        {
          return;
        }
      }
    } while (loopFlag);
  }

  // Selected item has 1 remaining qty
  else if (merchantItemQuantity[ITEM_INDEX] == 1)
  {
    purchaseAmount = 1;
  }

  // Selected item has 0 remaining qty
  else if (merchantItemQuantity[ITEM_INDEX] == 0)
  {
    purchaseAmount = 0;
    cout << "\tI'm fresh out of that item, check back later\n\n";
    return;
  }

  // Make sure the player has enough gold for the purchase
  if (goldCount >= purchaseAmount * merchantItemCost[ITEM_INDEX])
  {
    // Purchase confirmation loop
    char merchantConfirm = ' ';
    loopFlag = true;
    do
    {
      // Purchase confirmation with qty printed
      if (merchantItemQuantity[ITEM_INDEX] > 1)
      {
        cout << "\tConfirm purchase of " << purchaseAmount << "x " << merchantItemName[ITEM_INDEX] << " for x" << purchaseAmount * merchantItemCost[ITEM_INDEX] << " gold?\n";
      }

      // Purchase confirmation without qty printed
      else if (merchantItemQuantity[ITEM_INDEX] == 1)
      {
        cout << "\tConfirm purchase of " << merchantItemName[ITEM_INDEX] << " for x" << purchaseAmount * merchantItemCost[ITEM_INDEX] << " gold?\n";
      }

      cout << "\tY or N: ";
      cin >> merchantConfirm;
      if (validateDecision(merchantConfirm))
      {
        cout << "\n";
        loopFlag = false;
      }
    } while (loopFlag);

    // Player chose to purchase the item
    if (merchantConfirm == 'Y' || merchantConfirm == 'y')
    {
      if (merchantItemQuantity[ITEM_INDEX] > 1)
      {
        cout << "\t" << merchantItemName[ITEM_INDEX] << " x" << purchaseAmount << " acquired!\n\n";
      }
      else
      {
        cout << "\t" << merchantItemName[ITEM_INDEX] << " acquired!\n\n";
      }
    }

    // Player chose not to purchase the item
    else
    {
      purchaseAmount = 0;
    }
  }

  // Player couldn't afford the purchase
  else
  {
    purchaseAmount = 0;
    cout << "\tYou don't have enough gold!\n\n";
    return;
  }
}

// Pre-condition: called by roomController(), passed keyCount and gameVictory
// Post-condition: updates gameVictory to true if the player chooses to leave the dungeon - game ends
void roomExit(int &keyCount, bool &gameVictory)
{
  // Check if the player has the golden key
  if (keyCount > 0)
  {
    bool loopFlag = true;
    char selection = ' ';
    do
    {
      cout << "Would you like use your golden key to exit the dungeon?\n"
           << "Y or N:";
      cin >> selection;
      if (validateDecision(selection))
      {
        loopFlag = false;
      }
    } while (loopFlag);

    // Player chose to leave the dungeon, victory!
    if (selection == 'Y' || selection == 'y')
    {
      cout << "\n";
      gameVictory = true;
      doorArt();
      return;
    }
  }

  // Player doesn't have a golden key
  else
  {
    cout << "You don't have a golden key!\n\n";
  }
}

// Pre-condition: called by roomEnemy(), passed inventory variables, enemyProgression, rewardTier and className / characterStats
// Post-condition: returns 1 if the player won the battle, -1 if the player ran away, 0 if they lost, updates inventory variables, playerHealth, and updates rewardTier based on battleEnemySpawner()
int battleController(const string &className, int &rewardTier, int &potionCount, int armorCount, int enemyProgression, std::ifstream &characterStats)
{
  // Player health variable
  static int playerHealth = 20;

  if (debug)
  {
    playerHealth = 100;
  }

  // Fills skill names with default names based on class selection
  static string meleeName = " ", magicName = " ", rangedName = " ";
  static bool initializeNames = false;
  if (!initializeNames)
  {
    string upgradeMessage = " ";
    skillNames(meleeName, "Melee", upgradeMessage, className);
    skillNames(magicName, "Magic", upgradeMessage, className);
    skillNames(rangedName, "Ranged", upgradeMessage, className);
    initializeNames = true;
  }

  // Enemy Spawner
  int enemyTier = 0, enemyHealth = 0;
  string enemyName = " ";
  bool boss = false;
  battleEnemySpawner(enemyTier, rewardTier, enemyHealth, enemyName, enemyProgression, boss);

  // Battle loop - loops until either the enemy or the player hits 0 health
  while (enemyHealth > 0 && playerHealth > 0)
  {
    // Displays the battleMenu and the player's choice is stored in battleMenuSelection
    int battleMenuSelection = battleMenu(meleeName, magicName, rangedName, playerHealth, enemyHealth);

    // Player chose a damaging move
    if (battleMenuSelection >= 1 && battleMenuSelection <= 3)
    {
      // Subtracts playerDamage from enemyHealth, playerDamage passes the value from battleMenu to select a skill type (melee, mage, ranged)
      enemyHealth -= playerDamage(battleMenuSelection, meleeName, magicName, rangedName, className, enemyName, boss, characterStats);

      // The enemy is permitted to attack only if their health is > 0, this prevents the enemy from attacking after their health reaches 0
      if (enemyHealth > 0)
      {
        // Enemy damage is based on the (enemy tier * base enemy damage) + a random number between 1 and 3
        playerHealth -= enemyDamage(enemyTier, enemyName, boss, armorCount);
      }
    }

    // Player chose to heal
    else if (battleMenuSelection == 4)
    {
      // A random heal amount is added to playerHealth
      playerHealth += heal(potionCount);

      // Enemy damage is based on the (enemy tier * base enemy damage) + a random number between 1 and 3
      playerHealth -= enemyDamage(enemyTier, enemyName, boss, armorCount);
    }

    // Player chose to run
    else if (battleMenuSelection == 5)
    {
      // Player has a 50% chance to successfully run, Bards can always run
      if (className == "Bard" || 1 + (rand() % 100) <= 50)
      {
        cout << "\tYou escaped successfully!\n\n";
        // Returning a -1 means successful escape
        return -1;
      }

      // Player failed to run
      else
      {
        cout << "\tYou failed to escape!\n\n";
        // Enemy damage is based on the (enemy tier * base enemy damage) + a random number between 1 and 3
        playerHealth -= enemyDamage(enemyTier, enemyName, boss, armorCount);
      }
    }
  }

  // Checks if the player won the battle
  if (enemyHealth <= 0)
  {
    cout << "Enemy defeated!\n\n";
    // Returning a 1 means the player won the battle
    return 1;
  }

  // Checks if the player lost the battle
  if (playerHealth <= 0)
  {
    cout << "Player Defeated!\n\n";
    // Returning a 0 means the player lost the battle
    return 0;
  }
}

// Pre-condition: called by battleController(), passed enemy variables
// Post-condition: updates all enemy variables based on enemyProgression
void battleEnemySpawner(int &enemyTier, int &rewardTier, int &enemyHealth, string &enemyName, int enemyProgression, bool &boss)
{
  // Randomizer variable for enemyTier
  int randomTier = 1 + (rand() % 100);

  // Variables for Tier chance
  int tier1 = 0, tier2 = 0, tier3 = 0, tier4 = 0, tier5 = 0;

  // The first 5 rooms can spawn enemies Tier 1-2
  if (enemyProgression < 5)
  {
    if (randomTier <= 80)
    {
      enemyTier = 1;
    }
    else
    {
      enemyTier = 2;
    }
  }

  // The next 5 rooms can spawn enemies Tier 1-3
  else if (enemyProgression < 10)
  {
    // Calculates a random tier for the enemy - 60% chance of Tier 1, 30% chance of Tier 2, 10% chance of Tier 3
    tier1 = 60, tier2 = tier1 + 30;
    if (randomTier <= tier1)
    {
      enemyTier = 1;
    }
    else if (randomTier <= tier2)
    {
      enemyTier = 2;
    }
    else
    {
      enemyTier = 3;
    }
  }

  // The next 5 rooms can spawn enemies Tier 1-4
  else if (enemyProgression < 15)
  {
    // Calculates a random tier for the enemy - 35% chance of Tier 1, 30% chance of Tier 2, 25% chance of Tier 3, 10% chance of Tier 4
    tier1 = 35, tier2 = tier1 + 30, tier3 = tier2 + 25;
    if (randomTier <= tier1)
    {
      enemyTier = 1;
    }
    else if (randomTier <= tier2)
    {
      enemyTier = 2;
    }
    else if (randomTier <= tier3)
    {
      enemyTier = 3;
    }
    else
    {
      enemyTier = 4;
    }
  }

  // The final rooms can spawn enemies Tier 2-5
  else
  {
    // Calculates a random tier for the enemy - 35% chance of Tier 2, 25% chance of Tier 3, 20% chance of Tier 4, 15% chance of Tier 5, 5% chance of BOSS
    tier2 = 35, tier3 = tier2 + 25, tier4 = tier3 + 20, tier5 = tier4 + 15;
    if (randomTier <= tier2)
    {
      enemyTier = 2;
    }
    else if (randomTier <= tier3)
    {
      enemyTier = 3;
    }
    else if (randomTier <= tier4)
    {
      enemyTier = 4;
    }
    else if (randomTier <= tier5)
    {
      enemyTier = 5;
    }
    else
    {
      boss = true;
    }
  }

  // Establish non-boss enemy values
  if (!boss)
  {
    // Calculates health of the enemy based off of base enemy health and enemy tier
    enemyHealth = BASE_ENEMY_HEALTH * enemyTier;

    // Assigns a random name to the enemy
    int randomEnemyName = 0;
    int randomValue = 1 + (rand() % 100);
    if (enemyProgression < 5)
    {
      // 90% chance of enemies 1 - 2
      if (randomValue <= 90)
      {
        randomEnemyName = 1 + (rand() % 2);
      }
      // 10% chance of enemy 3
      else
      {
        randomEnemyName = 3;
      }
    }
    if (enemyProgression < 10)
    {
      // 70% chance of enemies 1 - 2
      if (randomValue <= 70)
      {
        randomEnemyName = 1 + (rand() % 2);
      }
      // 30% chance of enemy 3
      else
      {
        randomEnemyName = 3;
      }
    }
    else if (enemyProgression < 15)
    {
      // 70% chance of enemies 1, 2, 4, or 5
      if (randomValue < 70)
      {
        bool goodValue = false;
        int randomValueAgain = 0;
        do
        {
          randomValueAgain = rand() % 4;
          if (randomValueAgain != 1)
          {
            goodValue = true;
          }
        } while (!goodValue);
        randomEnemyName = 1 + (rand() % 2) + randomValueAgain;
      }
      // 30% chance of enemy 3
      else
      {
        randomEnemyName = 3;
      }
    }
    else
    {
      // 40% chance of enemies 1 - 4
      if (randomValue <= 40)
      {
        randomEnemyName = 1 + (rand() % 4);
      }
      // 60% chance of enemies 4 - 6
      else
      {
        randomEnemyName = 4 + (rand() % 3);
      }
    }

    switch (randomEnemyName)
    {
      case 1:
      {
        enemyName = "Goblin"; // Weak to Melee, Neutral to Ranged, Neutral to Melee
        break;
      }
      case 2:
      {
        enemyName = "Orc"; // Weak to Magic, Neutral to Ranged, Neutral to Melee
        break;
      }
      case 3:
      {
        enemyName = "Troll"; // Weak to Ranged and Melee, Neutral to Magic
        enemyHealth *= 2;
        break;
      }
      case 4:
      {
        enemyName = "Skeleton"; // Weak to Melee, Neutral to Magic, Resistant to Ranged
        break;
      }
      case 5:
      {
        enemyName = "Cyclops"; // Neutral to Melee, Neutral to Magic, Neutral to Ranged
        break;
      }
      case 6:
      {
        enemyName = "Minotaur"; // Weak to Ranged and Magic, Resistant to Melee
        enemyHealth *= 2;
        break;
      }
    }

    // Print enemy attributes
    cout << "A tier " << enemyTier << " " << enemyName << " is guarding this room!\n\n";
    rewardTier = enemyTier; // Reward tier is used to control loot drops
  }

  // Establish enemy values as boss values
  else
  {
    // Boss health
    enemyHealth = BOSS_HEALTH;
    rewardTier = 10; // This value is only used to control loot drops
    int randomBossName = 1 + (rand() % 10);

    // Assigns a random boss name
    switch (randomBossName)
    {
      case 1:
      {
        enemyName = "Voidshaper Nihilus";
        break;
      }
      case 2:
      {
        enemyName = "Snarltooth the Feral";
        break;
      }
      case 3:
      {
        enemyName = "Dreadlord Vorkar";
        break;
      }
      case 4:
      {
        enemyName = "Soulstealer Malgrimor";
        break;
      }
      case 5:
      {
        enemyName = "King Rattleclaw";
        break;
      }
      case 6:
      {
        enemyName = "Ignatius the Infernal";
        break;
      }
      case 7:
      {
        enemyName = "Dreadmaw the Bonecrusher";
        break;
      }
      case 8:
      {
        enemyName = "Rotclaw the Pustulant";
        break;
      }
      case 9:
      {
        enemyName = "Sludgeheart the Grotesque";
        break;
      }
      case 10:
      {
        enemyName = "Drak'thar the Trollking";
        break;
      }
    }

    // Some cool boss spawning text
    cout << "\nThe Earth trembles beneath you, a powerful foe is near...\n"
         << enemyName << " has cornered you!\n\n";
  }
}

// Pre-condition: called by battleController(), passed skill and health variables
// Post-condition: returns user selection from displayed battleMenu
int battleMenu(string &meleeName, string &magicName, string &rangedName, int playerHealth, int enemyHealth)
{
  // Menu Variables
  int boxWidth = 63;
  int borderSpacing = ((boxWidth - 23) / 2);
  string choiceName[] = {meleeName, magicName, rangedName};

  short int battleMenuSelection = 0;
  bool loopFlag = true;
  do
  {
    battleHealthArt(playerHealth, enemyHealth);
    cout << "." << setfill('-') << setw(boxWidth) << ".\n"
         << "|" << setfill(' ') << setw(boxWidth) << "|\n"
         << "|" << setw(12) << " " << "1. " << choiceName[0] << setw(borderSpacing - choiceName[0].length()) << " " << "4. Heal" << setw(18) << " " << " |\n"
         << "|" << setw(12) << " " << "2. " << choiceName[1] << setw( borderSpacing - choiceName[1].length()) << " " << "5. Run Away" << setw(14) << " " << " |\n"
         << "|" << setw(12) << " " << "3. " << choiceName[2] << setw(borderSpacing - choiceName[2].length()) << " " << "6. Help" << setw(18) << " " << " |\n"
         << "|" << setfill(' ') << setw(boxWidth) << "|\n"
         << "'" << setfill('-') << setw(boxWidth) << "'\n"
         << setfill(' ') << "\n"
         << "\tMake a selection: ";
    battleMenuSelection = 0;
    cin >> battleMenuSelection;
    if (validateInput(battleMenuSelection, 1, 6))
    {
      if (battleMenuSelection != 6)
      {
        loopFlag = false;
      }
      else
      {
        cout << "\n";
        tutorialBattle();
      }
    }
  } while (loopFlag);
  cout << "\n";
  return battleMenuSelection;
}

// Pre-condition: called by battleMenu(), passed health variables
// Post-condition: displays health art
void battleHealthArt(int playerHealth, int enemyHealth)
{
  // Don't print health if either the player or the enemy has 0 health
  if (playerHealth <= 0 || enemyHealth <= 0)
  {
    return;
  }

  // Print health
  else
  {
    string playerHealthDisplay = "Player health: ";
    playerHealthDisplay += std::to_string(playerHealth);
    string enemyHealthDisplay = "Enemy health: ";
    enemyHealthDisplay += std::to_string(enemyHealth);

    // Check amount of playerHealth digits to determine offset for blank spacing between player and enemy health boxes
    int offset = 1;
    int playerHealthDigits = (std::to_string(playerHealth)).length();
    for (int i = 1; i < playerHealthDigits; ++i)
    {
      --offset;
    }

    cout << "." << setfill('-') << setw(5 + playerHealthDisplay.length()) << "." << setfill(' ') << setw(offset + 34 - enemyHealthDisplay.length()) << " " << "." << setfill('-') << setw(6 + enemyHealthDisplay.length()) << ".\n"
         << "|" << setfill(' ') << setw(2) << " " << playerHealthDisplay << setw(2) << " " << "|" << setw(offset + 34 - enemyHealthDisplay.length()) << " " << "|" << setw(2) << " " << enemyHealthDisplay << setw(4) << "|\n"
         << "'" << setfill('-') << setw(5 + playerHealthDisplay.length()) << "'" << setfill(' ') << setw(offset + 34 - enemyHealthDisplay.length()) << " " << "'" << setfill('-') << setw(6 + enemyHealthDisplay.length()) << "'\n"
         << setfill(' ');
  }
}

// Pre-condition: called by battleController(), passed result of battleMenu(), skill variables, enemy variables, and characterStats
// Post-condition: returns a damage amount based on all passed variables
float playerDamage(int battleMenuSelection, string &meleeName, string &magicName, string &rangedName, const string &className, const string &enemyName, bool boss, std::ifstream &characterStats)
{
  // Pull values from characterStats
  static int meleeSkill, magicSkill, rangedSkill;
  static float critSkill = 1.0;
  static bool statsRead = false;
  if (!statsRead)
  {
    string classNameChecker = " ";
    // Ignore the first two lines (info header and blank line)
    std::getline(characterStats, classNameChecker);
    std::getline(characterStats, classNameChecker);
    while (characterStats.good() && !statsRead)
    {
      // Read the class name
      std::getline(characterStats, classNameChecker, ',');
      // Check the class name
      if (classNameChecker == className)
      {
        characterStats >> meleeSkill >> rangedSkill >> magicSkill >> critSkill;
        statsRead = true;
      }
      // Check the next line if className doesn't match
      else
      {
        std::getline(characterStats, classNameChecker);
      }
    }
  }

  // Counters that are used to move through the tiers of skill milestones
  static int meleeCounter, magicCounter, rangedCounter;

  // Variables to track current skill values
  int *skillCounter = nullptr;
  string skillName = " ";
  int skillUpgradeIndex = 0;

  // Damage Variables
  float critChance = BASE_CRIT_CHANCE * critSkill;
  float damageValue = 0;

  switch (battleMenuSelection)
  {
    // Melee
    case 1:
    {
      skillCounter = &meleeCounter;
      skillName = meleeName;
      skillUpgradeIndex = 0;
      damageValue = BASE_MELEE_DAMAGE * meleeSkill;
      break;
    }
    // Magic
    case 2:
    {
      skillCounter = &magicCounter;
      skillName = magicName;
      skillUpgradeIndex = 1;
      damageValue = BASE_MAGIC_DAMAGE * magicSkill;
      break;
    }
    // Ranged
    case 3:
    {
      skillCounter = &rangedCounter;
      skillName = rangedName;
      skillUpgradeIndex = 2;
      damageValue = BASE_RANGED_DAMAGE * rangedSkill;
      break;
    }
  }

  // Check skill tier for damage calculations
  int skillTier = 0;
  // Level 1
  if (*skillCounter < SKILL_UPGRADE)
  {
    skillTier = 1;
    ++(*skillCounter);
  }
  // Level 2
  else if (*skillCounter >= SKILL_UPGRADE && *skillCounter < SKILL_UPGRADE * 2)
  {
    skillTier = 2;
    ++(*skillCounter);
  }
  // Level 3
  else if (*skillCounter >= SKILL_UPGRADE * 2)
  {
    skillTier = 3;
    ++(*skillCounter);
  }

  // Calculate damageValue
  damageValue *= skillTier * weaponUpgrade(skillUpgradeIndex) * enemyResistance(skillName, enemyName, boss, battleMenuSelection);

  // Add a small offset to the damage for a touch of variability
  damageValue += (-1 + (rand() % 3)) * skillTier;

  // Calculate crit
  if (1 + (rand() % 100) <= critChance * 100)
  {
    damageValue *= 2;
    cout << "\tYou landed a critical hit!\n";
  }

  // DEBUG OPTION - Max damage
  if (debug)
  {
    damageValue = 100;
  }

  cout << "\t" << skillName << " dealt " << static_cast<int>(damageValue) << " damage\n\n";

  // Print skill upgrade notification
  if (*skillCounter == SKILL_UPGRADE || *skillCounter == SKILL_UPGRADE * 2)
  {
    // Upgrade messages for displayMeInABox function
    string congratulationsMessage = "Congratulations!";
    string upgradeMessage = " ";

    // Bools to make sure messages only prints once
    static bool melee2Once = false, melee3Once = false;
    static bool magic2Once = false, magic3Once = false;
    static bool ranged2Once = false, ranged3Once = false;

    if (meleeCounter == SKILL_UPGRADE)
    {
      if (!melee2Once)
      {
        skillNames(meleeName, "Melee", upgradeMessage, className, 2);
        displayMeInABox(congratulationsMessage,upgradeMessage);
        melee2Once = true;
      }
    }
    else if (meleeCounter == SKILL_UPGRADE * 2)
    {
      if (!melee3Once)
      {
        skillNames(meleeName, "Melee", upgradeMessage, className, 3);
        displayMeInABox(congratulationsMessage,upgradeMessage);
        melee3Once = true;
      }
    }

    if (magicCounter == SKILL_UPGRADE)
    {
      if (!magic2Once)
      {
        skillNames(magicName, "Magic", upgradeMessage, className, 2);
        displayMeInABox(congratulationsMessage,upgradeMessage);
        magic2Once = true;
      }
    }
    else if (magicCounter == SKILL_UPGRADE * 2 && !magic3Once)
    {
      if (!magic3Once)
      {
        skillNames(magicName, "Magic", upgradeMessage, className, 3);
        displayMeInABox(congratulationsMessage,upgradeMessage);
        magic3Once = true;
      }
    }

    if (rangedCounter == SKILL_UPGRADE)
    {
      if (!ranged2Once)
      {
        skillNames(rangedName, "Ranged", upgradeMessage, className, 2);
        displayMeInABox(congratulationsMessage,upgradeMessage);
        ranged2Once = true;
      }
    }
    else if (rangedCounter == SKILL_UPGRADE * 2)
    {
      if (!ranged3Once)
      {
        skillNames(rangedName, "Ranged", upgradeMessage, className, 3);
        displayMeInABox(congratulationsMessage, upgradeMessage);
        ranged3Once = true;
      }
    }
  }

  return damageValue;
}

// Pre-condition: called by playerDamage(), passed damageValue, skill variables, enemy variables, and result of battleMenu()
// Post-condition: updates damageValue based on enemy stats
float enemyResistance(const string &abilityName, const string &enemyName, bool boss, int battleMenuSelection)
{
  float resistanceValue = 1.00;

  if (!boss)
  {
    if (enemyName == "Goblin")
    {
      switch (battleMenuSelection)
      {
        // Goblin is weak to Melee, but neutral to the rest
        case 1:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        default:
        {
          resistanceValue = 1.0;
          break;
        }
      }
    }
    else if (enemyName == "Orc")
    {
      switch (battleMenuSelection)
      {
        // Orc is weak to Magic, Neutral to the rest
        case 2:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        default:
        {
          resistanceValue = 1.0;
          break;
        }
      }
    }
    else if (enemyName == "Troll")
    {
      switch (battleMenuSelection)
      {
        // Troll is weak to Ranged and Melee, Neutral to Magic
        case 1:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        case 3:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        default:
        {
          resistanceValue = 1.0;
          break;
        }
      }
    }
    else if (enemyName == "Skeleton")
    {
      switch (battleMenuSelection)
      {
        // Skeleton is weak to Melee, Neutral to Magic, and Resistant to Ranged
        case 1:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        case 2:
        {
          resistanceValue = 1.0;
          break;
        }
        case 3:
        {
          resistanceValue = 0.5;
          cout << "\t" << abilityName << " is disappointingly ineffective against " << enemyName << "\n\n";
          break;
        }
      }
    }
    else if (enemyName == "Cyclops")
    {
      resistanceValue = 1.0;
    }
    else if (enemyName == "Minotaur")
    {
      switch (battleMenuSelection)
      {
        // Minotaur is weak to Ranged and Magic, Resistant to Melee
        case 1:
        {
          resistanceValue = 0.5;
          cout << "\t" << abilityName << " is disappointingly ineffective against " << enemyName << "\n\n";
          break;
        }
        case 2:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
        case 3:
        {
          resistanceValue = 2.0;
          cout << "\t" << abilityName << " is incredibly effective against " << enemyName << "!\n\n";
          break;
        }
      }
    }
  }

  // Players deal triple damage vs. bosses
  else
  {
    resistanceValue = 3.0;
  }

  return resistanceValue;
}

// Pre-condition: called by battleController(), passed enemy variables
// Post-condition: returns a damage amount based on enemy attributes
float enemyDamage(int enemyTier, const string &enemyName, bool boss, int armorCount)
{
  float damage = 0;
  if (!boss)
  {
    damage = (BASE_ENEMY_DAMAGE * enemyTier) + (1 + (rand() % 3));
    if (enemyTier > 3)
    {
      damage *= 0.85f;
    }
  }
  else
  {
    damage = BOSS_DAMAGE_LOW + (rand() % (BOSS_DAMAGE_HIGH + 1 - BOSS_DAMAGE_LOW));
  }

  damage -= armorCount;

  // One-shot protection
  if (damage > 19)
  {
    damage = 19;
  }

  // Stops players from healing when stacking a bunch of armor
  if (damage < 0)
  {
    damage = 0;
  }

  cout << "\t" << enemyName << " dealt " << static_cast<int>(damage) << " damage\n\n";
  return damage;
}

// Pre-condition: called by playerDamage(), passed skill variables, upgradeMessage, and tier override
// Post-condition: updates skillName and upgradeMessage based on tier and skillType
void skillNames(string &skillName, const string &skillType, string &upgradeMessage, const string &className, int tier)
{
  // Function was called to upgrade the skill
  if (tier > 1)
  {
    // Warrior Skills
    if (className == "Warrior")
    {
      switch (tier)
      {
        // Level 2 Skills
        case 2:
        {
          if (skillType == "Melee") // Slash | Cleave | Behemoth Strike
          {
            skillName = "Cleave";
            upgradeMessage = "Slash has been upgraded to Cleave";
          }
          else if (skillType == "Magic") // Shield Charge | Vortex Slam | Arcane Lunge
          {
            skillName = "Vortex Slam";
            upgradeMessage = "Shield Charge has been upgraded to Vortex Slam";
          }
          else if (skillType == "Ranged") // Rock Throw | Shield Throw | Javelin Toss
          {
            skillName = "Shield Throw";
            upgradeMessage = "Rock Throw has been upgraded to Shield Throw";
          }
          break;
        }

        // Level 3 Skills
        case 3:
        {
          if (skillType == "Melee")
          {
            skillName = "Behemoth Strike";
            upgradeMessage = "Cleave has been upgraded to Behemoth Strike";
          }
          else if (skillType == "Magic")
          {
            skillName = "Arcane Lunge";
            upgradeMessage = "Vortex Slam has been upgraded to Arcane Lunge";
          }
          else if (skillType == "Ranged")
          {
            skillName = "Javelin Toss";
            upgradeMessage = "Shield Throw has been upgraded to Javelin Toss";
          }
          break;
        }
      }
    }

    // Mage Skills
    else if (className == "Mage")
    {
      switch (tier)
      {
        // Level 2 Skills
        case 2:
        {
          if (skillType == "Melee") // Bonk | Whack | Astral Thump
          {
            skillName = "Whack";
            upgradeMessage = "Bonk has been upgraded to Whack";
          }
          else if (skillType == "Magic") // Frost Blast | Arctic Veil | Flash Freeze
          {
            skillName = "Arctic Veil";
            upgradeMessage = "Frost Blast has been upgraded to Arctic Veil";
          }
          else if (skillType == "Ranged") // Zap | Thunderbolt | Thunderstorm
          {
            skillName = "Thunderbolt";
            upgradeMessage = "Zap has been upgraded to Thunderbolt";
          }
          break;
        }

        // Level 3 Skills
        case 3:
        {
          if (skillType == "Melee")
          {
            skillName = "Astral Thump";
            upgradeMessage = "Whack has been upgraded to Astral Thump";
          }
          else if (skillType == "Magic")
          {
            skillName = "Flash Freeze";
            upgradeMessage = "Arctic Veil has been upgraded to Flash Freeze";
          }
          else if (skillType == "Ranged")
          {
            skillName = "Thunderstorm";
            upgradeMessage = "Thunderbolt has been upgraded to Thunderstorm";
          }
          break;
        }
      }
    }

    // Archer Skills
    else if (className == "Archer")
    {
      switch (tier)
      {
        // Level 2 Skills
        case 2:
        {
          if (skillType == "Melee") // Slice | Sever | Blade Dance
          {
            skillName = "Sever";
            upgradeMessage = "Slice has been upgraded to Sever";
          }
          else if (skillType == "Magic") // Poison Bomb | Intoxicate | Pestilence
          {
            skillName = "Intoxicate";
            upgradeMessage = "Poison Bomb has been upgraded to Intoxicate";
          }
          else if (skillType == "Ranged") // Pierce | Perforate | Serpent Shot
          {
            skillName = "Perforate";
            upgradeMessage = "Pierce has been upgraded to Perforate";
          }
          break;
        }

        // Level 3 Skills
        case 3:
        {
          if (skillType == "Melee")
          {
            skillName = "Blade Dance";
            upgradeMessage = "Sever has been upgraded to Blade Dance";
          }
          else if (skillType == "Magic")
          {
            skillName = "Pestilence";
            upgradeMessage = "Intoxicate has been upgraded to Pestilence";
          }
          else if (skillType == "Ranged")
          {
            skillName = "Serpent Shot";
            upgradeMessage = "Perforate has been upgraded to Serpent Shot";
          }
          break;
        }
      }
    }

    // Bard Skills
    else if (className == "Bard")
    {
      switch (tier)
      {
        // Level 2 Skills
        case 2:
        {
          if (skillType == "Melee") // Slap | Snuggle | Strum
          {
            skillName = "Snuggle";
            upgradeMessage = "Slap has been upgraded to Snuggle";
          }
          else if (skillType == "Magic") // Beg | Sing | Serenade
          {
            skillName = "Sing";
            upgradeMessage = "Beg has been upgraded to Sing";
          }
          else if (skillType == "Ranged") // Waft | Whistle | Seduce
          {
            skillName = "Whistle";
            upgradeMessage = "Waft has been upgraded to Whistle";
          }
          break;
        }

        // Level 3 Skills
        case 3:
        {
          if (skillType == "Melee")
          {
            skillName = "Strum";
            upgradeMessage = "Snuggle has been upgraded to Strum";
          }
          else if (skillType == "Magic")
          {
            skillName = "Serenade";
            upgradeMessage = "Sing has been upgraded to Serenade";
          }
          else if (skillType == "Ranged")
          {
            skillName = "Seduce";
            upgradeMessage = "Whistle has been upgraded to Seduce";
          }
          break;
        }
      }
    }
  }

  // Function was called to initialize skill names
  else
  {
    // Warrior Skills
    if (className == "Warrior")
    {
      if (skillType == "Melee")
      {
        skillName = "Slash";
      }
      else if (skillType == "Magic")
      {
        skillName = "Shield Charge";
      }
      else if (skillType == "Ranged")
      {
        skillName = "Rock Throw";
      }
    }

    // Mage Skills
    else if (className == "Mage")
    {
      if (skillType == "Melee")
      {
        skillName = "Bonk";
      }
      else if (skillType == "Magic")
      {
        skillName = "Frost Blast";
      }
      else if (skillType == "Ranged")
      {
        skillName = "Zap";
      }
    }

    // Archer Skills
    else if (className == "Archer")
    {
      if (skillType == "Melee")
      {
        skillName = "Slice";
      }
      else if (skillType == "Magic")
      {
        skillName = "Poison Bomb";
      }
      else if (skillType == "Ranged")
      {
        skillName = "Pierce";
      }
    }

    // Bard Skills
    else if (className == "Bard")
    {
      if (skillType == "Melee")
      {
        skillName = "Slap";
      }
      else if (skillType == "Magic")
      {
        skillName = "Beg";
      }
      else if (skillType == "Ranged")
      {
        skillName = "Waft";
      }
    }
  }
}

// Pre-condition: called by playerDamage() or roomMerchant(), the second argument (defaulted to -1) determines whether the function is being called to check upgradeCounter (playerDamage()) or to increment it (roomMerchant())
// Post-condition: returns upgradeCounter, if called by roomMerchant() - returns 0
int weaponUpgrade(int checkWeaponUpgrade, int upgradeThis)
{
  // Initialize upgrade array
  static int upgradeCounter[] = {1,1,1};
  const int MELEE_WEAPON = 0, MAGIC_WEAPON = 1, RANGED_WEAPON = 2;

  // Function was called to check upgradeCounter
  if (upgradeThis == -1)
  {
    switch (checkWeaponUpgrade)
    {
      case 0:
      {
        return upgradeCounter[MELEE_WEAPON];
      }
      case 1:
      {
        return upgradeCounter[MAGIC_WEAPON];
      }
      case 2:
      {
        return upgradeCounter[RANGED_WEAPON];
      }
    }
  }

  // Function was called to increment upgradeCounter indexes
  else
  {
    switch (upgradeThis)
    {
      // Melee is upgraded
      case 0:
      {
        ++upgradeCounter[MELEE_WEAPON];
        break;
      }
      // Magic is upgraded
      case 1:
      {
        ++upgradeCounter[MAGIC_WEAPON];
        break;
      }
      // Ranged is upgraded
      case 2:
      {
        ++upgradeCounter[RANGED_WEAPON];
        break;
      }
    }
  }
  return 0;
}

// Pre-condition: called by battleController(), passed potionCount
// Post-condition: returns an amount to heal the player and updates potionCount
int heal(int &potionCount)
{
  // If you have a potion, heal
  if (potionCount > 0)
  {
    // Picks a random number between 10 and 20 to return a heal amount
    int healValue = 10 + (rand() % 11);
    cout << "\tYou used a potion and healed for " << healValue << " health\n"
         << "\tYou now have " << --potionCount << " potions.\n\n";
    // Returns the amount the player will be healed
    return healValue;
  }

  // If the player doesn't have any potions
  else
  {
    cout << "\tYou don't have any potions!\n";
    return 0;
  }
}

// Pre-condition: called to validate a Y or N decision
// Post-condition: returns whether the choice was valid or not
bool validateDecision(int userChoice)
{
  bool validFlag = true;
  if ((cin.fail()) || (!(userChoice == 'Y' || userChoice == 'y' || userChoice == 'N' || userChoice == 'n')))
  {
    cout << setw(63) << "Invalid Selection! >:(\n"
         << setw(63) << "Please enter an acceptable value\n"
         << "\n";
    validFlag = false;
  }
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return validFlag;
}

// Pre-condition: called to validate a number input
// Post-condition: returns whether the choice was valid or not
bool validateInput(int userChoice, int rangeLow, int rangeHigh)
{
  bool validFlag = true;
  if ((cin.fail()) || ((userChoice < rangeLow) || (userChoice > rangeHigh)))
  {
    cout << setw(63) << "Invalid Selection! >:( \n"
         << setw(63) << "Please enter an acceptable value\n"
         << "\n";
    validFlag = false;
  }
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return validFlag;
}

// Pre-condition: called to validate a direction input, passed userChoice
// Post-condition: returns whether the choice was valid or not, updates userChoice value to uppercase
bool validateDirection(int rowPosition, int columnPosition, char &userChoice)
{
  bool validFlag = true;
  if ((cin.fail()) || (!(userChoice == 'N' || userChoice == 'n' || userChoice == 'E' || userChoice == 'e' || userChoice == 'S' || userChoice == 's' || userChoice == 'W' || userChoice == 'w')))
  {
    cout << setw(63) << "Invalid Selection! >:(\n"
         << setw(63) << "Please enter an acceptable value\n"
         << "\n";
    validFlag = false;
  }
  else
  {
    // Convert the char to uppercase for use in switch statements
    if (userChoice == 'n' || userChoice == 'e' || userChoice == 's' || userChoice == 'w')
    {
      userChoice -= 32;
    }

    // Bounds checking
    string boundsFail = "A mysterious force prevents you from progressing in that direction...\n\n";
    switch (userChoice)
    {
      case 'N':
      {
        if (--rowPosition < 0)
        {
          cout << boundsFail;
          validFlag = false;
        }
        break;
      }
      case 'S':
      {
        if (++rowPosition > MAP_ROWS - 1)
        {
          cout << boundsFail;
          validFlag = false;
        }
        break;
      }
      case 'E':
      {
        if (++columnPosition > MAP_COLUMNS - 1)
        {
          cout << boundsFail;
          validFlag = false;
        }
        break;
      }
      case 'W':
      {
        if (--columnPosition < 0)
        {
          cout << boundsFail;
          validFlag = false;
        }
        break;
      }
    }
  }
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return validFlag;
}

// Pre-condition: called to display text in a box
// Post-condition: displays text in a box based on string length
void displayMeInABox(const string &message)
{
  // Offsets are used to clean up integer division spacing
  int offset = 0;
  if (message.length() % 2 == 0)
  {
    offset = 1;
  }

  // Adjusts box width based on message size
  int boxWidth = 0;
  int indent = 0;
  int borderSpacing = 0;
  if (message.length() < 36)
  {
    boxWidth = 46;
    indent = 10;
  }
  else
  {
    boxWidth = 56;
    indent = 5;
  }
  borderSpacing = ((boxWidth - 4) / 2);


  cout << setw(indent) << "." << setfill('-') << setw(boxWidth) << ".\n" << setfill(' ')
       << setw(indent) << "|" << setfill(' ') << setw(boxWidth) << "|\n"
       << setw(indent) << "|" << setw(offset + borderSpacing - message.length() / 2) << " " << message << setw(borderSpacing - message.length() / 2) << " " << " |\n"
       << setw(indent) << "|" << setfill(' ') << setw(boxWidth) << "|\n"
       << setw(indent) << "'" << setfill('-') << setw(boxWidth) << "'\n" << setfill(' ')
       << "\n";
}

// Pre-condition: overload - called to display text in a box
// Post-condition: displays text in a box based on string length
void displayMeInABox(const string &message1, const string &message2)
{
  // Offsets are used to clean up integer division spacing
  int offset1 = 0;
  int offset2 = 0;
  if (message1.length() % 2 == 0)
  {
    offset1 = 1;
  }
  if (message2.length() % 2 == 0)
  {
    offset2 = 1;
  }

  // Adjusts box width based on message size
  int boxWidth = 0;
  int indent = 0;
  int borderSpacing = 0;
  if (message2.length() < 36)
  {
    boxWidth = 46;
    indent = 10;
  }
  else
  {
    boxWidth = 56;
    indent = 5;
  }
  borderSpacing = ((boxWidth - 4) / 2);

  cout << setw(indent) << "." << setfill('-') << setw(boxWidth) << ".\n" << setfill(' ')
       << setw(indent) << "|" << setfill(' ') << setw(boxWidth) << "|\n"
       << setw(indent) << "|" << setw(offset1 + borderSpacing - message1.length() / 2) << " " << message1 << setw(borderSpacing - message1.length() / 2) << " " << " |\n"
       << setw(indent) << "|" << setw(offset2 + borderSpacing - message2.length() / 2) << " " << message2 << setw(borderSpacing - message2.length() / 2) << " " << " |\n"
       << setw(indent) << "|" << setfill(' ') << setw(boxWidth) << "|\n"
       << setw(indent) << "'" << setfill('-') << setw(boxWidth) << "'\n" << setfill(' ')
       << "\n";
}

// Pre-condition: called to display text in a box
// Post-condition: displays text in a box
void monologueInABox (const string &message)
{
  cout << "." << setfill('-') << setw(3 + message.length()) << "." << "\n" << setfill(' ')
       << "| " << message << " |\n"
       << "'" << setfill('-') << setw(3 + message.length()) << "'" << "\n\n" << setfill(' ');
}

// Pre-condition: called to display randomized roomEnemy text
// Post-condition: displays randomized room entry text
void roomEnemyMonologue(int dialogueSwitch)
{
  // Random dialogue selection
  int randomChoice = 1 + (rand() % 5);

  if (dialogueSwitch == 0)
  {
    switch (randomChoice)
    {
      case 1:
      {
        cout << "Something foul reeks beyond this door... \n";
        break;
      }
      case 2:
      {
        cout << "I feel the hairs on my arm stand up straight...\n";
        break;
      }
      case 3:
      {
        cout << "I've got a bad feeling about this...\n";
        break;
      }
      case 4:
      {
        cout << "What could possibly go wrong...\n";
        break;
      }
      case 5:
      {
        cout << "The creatures of the dungeon sense my presence...\n";
        break;
      }
    }
  }

  else
  {
    switch (randomChoice)
    {
      case 1:
      {
        cout << "This doesn't feel right... \n";
        break;
      }
      case 2:
      {
        cout << "I sense my previous victory has not cleansed this room of evil...\n";
        break;
      }
      case 3:
      {
        cout << "Something seems off...\n";
        break;
      }
      case 4:
      {
        cout << "What could it be...\n";
        break;
      }
      case 5:
      {
        cout << "I can't believe my eyes...\n";
        break;
      }
    }
  }
}

// Pre-condition: called to display randomized roomLoot text
// Post-condition: displays randomized room entry text
void roomLootMonologue(int dialogueSwitch)
{
  // Random dialogue selection
  int randomChoice = 1 + (rand() % 5);

  if (dialogueSwitch == 0)
  {
    switch (randomChoice)
    {
      case 1:
      {
        cout << "I notice a shimmering golden gleam between the cracks of this door...\n";
        break;
      }
      case 2:
      {
        cout << "What's this...\n";
        break;
      }
      case 3:
      {
        cout << "I've got a good feeling about this...\n";
        break;
      }
      case 4:
      {
        cout << "Do my eyes betray me...\n";
        break;
      }
      case 5:
      {
        cout << "I can't believe my eyes...\n";
        break;
      }
    }
    cout << "A magnificent golden chest sits in the middle of the room!\n\n";
  }

  else
  {
    switch (randomChoice)
    {
      case 1:
      {
        cout << "This doesn't feel right... \n";
        break;
      }
      case 2:
      {
        cout << "I sense my previous victory has not cleansed this room of evil...\n";
        break;
      }
      case 3:
      {
        cout << "Something seems off...\n";
        break;
      }
      case 4:
      {
        cout << "What could it be...\n";
        break;
      }
      case 5:
      {
        cout << "I can't believe my eyes...\n";
        break;
      }
    }
  }

}

// Pre-condition: called to display randomized roomMerchant text
// Post-condition: displays randomized room entry text
void roomMerchantMonologue(int dialogueSwitch)
{
  // Random dialogue selection
  int randomChoice = 1 + (rand() % 2);

  if (dialogueSwitch == 0)
  {
    switch (randomChoice)
    {
      case 1:
      {
        cout << "Welcome to my shop!\n";
        break;
      }
      case 2:
      {
        cout << "Greetings traveler!\n";
        break;
      }
    }
    cout << "Take a gander upon my wares...\n\n";
  }

  else
  {
    switch (randomChoice)
    {
      case 1:
      {
        cout << "Welcome back to my shop!\n";
        break;
      }
      case 2:
      {
        cout << "I'm glad to see you still in one piece!\n";
        break;
      }
    }
    cout << "I've found more supplies since we've last met...\n\n";
  }
}

// Pre-condition: called to display randomized roomExit text
// Post-condition: displays randomized room entry text
void roomExitMonologue(int dialogueSwitch)
{
  // Random dialogue selection
  int randomChoice = 1 + (rand() % 5);

  if (dialogueSwitch == 0)
  {
    switch (randomChoice)
    {
      default: // I haven't gotten around to writing more monologue yet
      {
        cout << "You notice a strange door, unlike any you've seen before. You're not sure why, but you feel it calling to you\n\n";
        break;
      }
    }
  }

  else
  {
    switch (randomChoice)
    {
      default: // I haven't gotten around to writing more monologue yet
      {
        cout << "You feel an overwhelming urge pulling you towards this room\n\n";
        break;
      }
    }
  }
}

// Pre-condition: called to display warrior art
// Post-condition: displays art
void warriorArt()
{
  cout << "                                                                             \n"
          "                   ..                                                        \n"
          "                   *                                                         \n"
          "                   #                                                         \n"
          "                  :+                                                         \n"
          "                  :=        -#%*--                                           \n"
          "                  .=      ::.   =+*                                          \n"
          "                  :-     :--.   .%#-   .:                                    \n"
          "                  --     =*+---: +*:  -#.*                                   \n"
          "                  =:   .##+-.=+==#-.   -++*-                                 \n"
          "                  -:  -%%:+.=-#@:.=*#- .-#+*-.                               \n"
          "                  -    -*:= +:  .-=%*= .++-=*+:                              \n"
          "                =*-  +=+%+*-=:.=+*#*%=%*=::::+*=                             \n"
          "               *+-:    =###+=+=--#%++*#=:-. : +-=                            \n"
          "              *=-== ...-*%%#*-::-@==+#=.-:. .:.-==.                          \n"
          "             .#--*- ---%%%+---*#+. =#::-: .     .-=:                         \n"
          "             .#+*#- +#**+%+:  :   -*-==- ..  .    .+=                        \n"
          "            +==+*#=.#: ##*:.. ..   -#--- . .       .=+                       \n"
          "           .#*=+%%+:    ::--::::.   :**--:.. . .   ..+=.                     \n"
          "           .=:=*%%+-     .=*+----...--+**+--.:.   :.:=++                     \n"
          "          .#=-=%@%+=       =##*++----::+##%+--. .  :--=+*                    \n"
          "           *.*###+*-.  .-:   *+*+::.:+#=  -*#:--:.--:====*                   \n"
          "           .#%@@=.-##.   .    +++-=+=  :#+%##= .-----=+=-++                  \n"
          "           :#@*= =*:.      +###+-#@*+: +@%*#+*=-=  ++++*==*:                 \n"
          "              ...:..:      =*+*=+*=###****. :=+=-=:. :-+=+*#                 \n"
          "               ..==-      -=**%. :.+%*++*%@:%-:   :::     :*:                \n"
          "                 .*.      =**#+:  :#@%###%*::==**-- -.                       \n"
          "                 :*-     :#*@+:.=%+#-  :%%=   .*+*%#+.                       \n"
          "                 %#*.    -+%%%*.-=++     +@::-:=.  -#-                       \n"
          "                  .       =*+**+=*#       :%%*#:-.-.:=-                      \n"
          "                           %*+#%@@           #%@%*:-+#-                      \n"
          "                          -*+@@%-              =@@#=--#=                     \n"
          "                        -*---=@+                 ##*++=%*+:                  \n"
          "                       %+::-:-#-                  +#*+-  .**                 \n"
          "                      =#+-::=**.                    =#=.   .#                \n"
          "                      =%---=%++                     +#*-    .*               \n"
          "                      =+=*#**:                       =+-:. ..:+              \n"
          "                      +#%#+#-                         .=-:..::               \n"
          "                      +%%%= ::.                         --:-.--              \n"
          "                     :#%%=.:=                            .==+--=-=           \n"
          "                     +#@%:   -.                            -=*+-+.           \n"
          "                    +*#@%:                                  :*###*           \n"
          "                    *@%#*                                    .#%+#*          \n"
          "                  .%@%*##.                                    +%*-+*         \n"
          "                  *#*+===-                                    *#%*==+:       \n"
          "                   :%+:-.                                    .#*+++====      \n"
          "                                                              -+%%*+===      \n"
          "                                                                :#%=         \n"
          "                                                                             \n";
}

// Pre-condition: called to display mage art
// Post-condition: displays art
void mageArt()
{
  cout << "                                                                             \n"
          "                                              ::                             \n"
          "                                            ..-+:-                           \n"
          "                                             --=+-.                          \n"
          "                           -*#+@#             :.                             \n"
          "                         .#=#*#%@%-         .:                               \n"
          "                         -: :++#%=@#%-      =:.:-                            \n"
          "                         : :.:.:##@@#**#-  .=::-%-                           \n"
          "                         =*-:=-:++#%%#%##+ =*=:=#+                           \n"
          "               :        =%---::::@@*@%%#*#*#%%+@@*                           \n"
          "               -.     =**#=.:-:-%%%#%*##:*+=%+-=*+                           \n"
          "              .+.    #+++*+:.. :- *%=.:+#===+*+:                             \n"
          "              .#    -#+####.:.-::++:.+#%+++=:                                \n"
          "              .+   ++=+*##=+=  . --..:-  =.                                  \n"
          "              .=  -#=*+=:.%@+- .  . .--:-+:                                  \n"
          "               -  =##+===+*=+*.:..  ..:... ...                               \n"
          "              -: .%=+  ++*%-==#:   -+*:   +  ..                              \n"
          "              .= :=*::::+%*===+=*#%*+*+=-:  ::..                             \n"
          "               +:+-+=---%@@+=:*+-++=#**%=   =-.:.                            \n"
          "               -:=%*==**%%%#+===#*++**##     :+--                            \n"
          "                . -=:**%%#@##*****%##+-++.     *:+:                          \n"
          "                - :*+*@@%#--:# -.+.#%#+=@@#   +    ::                        \n"
          "             -#*+=##*@@**#%%%+*#%+%%%@@#@@@@*:                               \n"
          "              :=-+--#@@*=++%%+*@#=*+#%#*@@@@@@#=:                            \n"
          "               *@@@@%@*++=+=-*@*-*+*#*=-=@@@@%@%#**                          \n"
          "               =%@@@@%--*=::*+=.==+##.=*+#@@@@%###*#*+-.                     \n"
          "               -#%%%%*:-%@+.:- -==+#+:+*=@@@#@#@@%%#+##*+:                   \n"
          "               .%%%#%-=*#*--..=+:=#**%+=*@@@@@@#**%###+=***+-                \n"
          "               :=%#@+.+-+.  .-::-#*+*#%%%%@@@@@@#*+*%#**+---==               \n"
          "               : @#%:-=+     :=:+#==*#%*=+@@@@@%%***=*#**+*=::=              \n"
          "               .*@%+ .:     =--=**=+=#%++*%@@@@%%%%%++++**+++=-:...          \n"
          "               :#@@=   -=-:*:-+++-%*+#%*+++@@#@%%%###*=*+==++==----::        \n"
          "               =+@@=   .--::-+++-#%**%%##@*#@@#*#%##*#*=+*=-.-.              \n"
          "               -:@@+    :.-+*#--#@*+%#*%++*+%@@#+*##**#*==*+.                \n"
          "              .=:@*+    :+#*=::%%%=**+%#****@@*##+*###*##+=++=-:             \n"
          "              :%@@*.   .-+::=*#%@=+*=#*%+#%@%@#*#%*#%+##* ..                 \n"
          "              :%@%+.   ::.#=+%%%+==+*=#*++@%+@@+*##:                         \n"
          "              =@@%.  . .:=++%%@%=-=++##*==#-*@@%**%-                         \n"
          "                -#     .:#+*%%@+*+++##%+=+=-*%@@##=                          \n"
          "                 .    ..:-**%+++*-=*#%*=+=-+++%@*-==                         \n"
          "                 -    .-:*##+-=--=*##%=+===++=%#%=:=*=                       \n"
          "                 -    -:+#@-:=:-*%%##*++-*+++=##%@+-=*+                      \n"
          "                :.-  .:-*#-:==%%%#%%#**-***==+-*%%@*=.                       \n"
          "                -.:  ::*#-:=+#%%%@#=+%==#+*+*==*+    :-                      \n"
          "               .-=  ::+%:===#%%@%-==#-=+##*+%%*+.   .=+                      \n"
          "               :=:.:::=-:=:+@@*++%@@+*#-++#%###%%@%#*.                       \n"
          "              -*=#+-...=*=+**+##*=%*-@*+:                                    \n"
          "             .@%+@@%*+--**+=. :#+=.                                          \n"
          "              -#%=%@*-##*.                                                   \n"
          "                                                                             \n";
}

// Pre-condition: called to display archer art
// Post-condition: displays art
void archerArt()
{
  cout << "                                                                             \n"
          "                     ::                                                      \n"
          "                    :+:                                                      \n"
          "                    ==                                                       \n"
          "                   :-:                                                       \n"
          "                   :-             .                                          \n"
          "                   .-          =.                                            \n"
          "                  . -..       :.      ..                                     \n"
          "                =*- --+*#+.-+=---.=-   ::                                    \n"
          "               :=:. =+=-%###         .:---                                   \n"
          "               -. . ---+=+--:         .*:                                    \n"
          "               =... -::=-*#==-.        .:          .                         \n"
          "               ==-: *#==#*+*:.+-             ::                              \n"
          "               :+*= #%%#--**+++=-#=-          =                              \n"
          "                =:  .=: :: **#**-:..:-.        :.                            \n"
          "                 *+:#. . +*:##%=.  ..:=:       :.                            \n"
          "          .++=+=*     .  ::#%%**.  .:-++                                     \n"
          "         :*--:+*#  : .:   ++**##+: .++++         .:.                         \n"
          "        -=#-==###-:+%-..  @=-=+*+@:.:*#*=                                    \n"
          "        *##**+++*+- +@#-*#==---==#:.-%##=-                                   \n"
          "          :**+**+*- *@@%**==.=-=*..-#%%*#=.                                  \n"
          "              .-  . +%@@#*++===**--++*%==+=                                  \n"
          "                  . + *+#*=+*=%%***#=:.=-=+                                  \n"
          "                  . =  %+#++%##**++*-++--++                                  \n"
          "                  ..-   #%#=**--*=-**+--=*=                                  \n"
          "                  : -.  -@@*%@@%@@@@***%#:+#                                 \n"
          "                  .:-.   :@#**#==*++#%%##*%+=+.                              \n"
          "                  .==:     @%#==++::-:.*=*%*++=                              \n"
          "                  :==#.--.     .=:-=% :.:#+**=--                             \n"
          "                  .+#    ....   -=++++=-::==#+=+.                            \n"
          "                   *:.  :::+*-::===-++#=*-=++%+*                             \n"
          "                   =. . .:.-=*%**#++=+*--:++:#=                              \n"
          "                    %=-=.=-:+++*++-*#%#.:++..:                               \n"
          "                    *+*#=:-=+###@##=-=+::*=.=-                               \n"
          "                    -#==*===:-+**%#%%%%- +=-+.                               \n"
          "                     #*-: +==  -%*##%@#: =- .                                \n"
          "                     + :*#-=-:.+###%##*-.-++=    .                           \n"
          "                    .+  =. -+=-.=#%#%-.-::==-  .**#-                         \n"
          "                    =-  =#%+--..*%#*  ==--=.  **==*#+                        \n"
          "                    *   *+: :=:-**%%#%*--:#**%#*-:-=+#                       \n"
          "                        =+*@@+*++=%+*@####++=##++--.-=+#:                    \n"
          "                       ---#:.-***:#+***::#+-+#+=+==-..----=                  \n"
          "                       *--+%*===+*=+=++-:+=-*#==-..:-=:..-:=+-+:             \n"
          "                       +-=#   :=+++*:-*+==                                   \n"
          "                        -=    ::+#*+-.                                       \n"
          "                       :-   .-==##=*                                         \n"
          "                      :   ::==+***##                                         \n"
          "                    =-  =-:-==%+:                                            \n"
          "                  -* ...-=++-                                                \n"
          "                  ----===-.                                                  \n"
          "                                                                             \n";
}

// Pre-condition: called to display bard art
// Post-condition: displays art
void bardArt()
{
  cout << "                                                                             \n"
          "                          @@%@@@%                                            \n"
          "                         @@%#%@@#%+                                          \n"
          "                        :@@@#*+*#*%+                  *                      \n"
          "                        =#@@%#-.:+-+:              : -.                      \n"
          "                         *@@*.:  :                   =                       \n"
          "                          #*%-.--:                 #*                        \n"
          "                         :##++++-+*-             .+#                         \n"
          "                       #%%#*#@@%@@%#+:           +-:                         \n"
          "                     .*%%****##%%%%##**+        +==                          \n"
          "                   -@@%%%#*++*##@%**###*+.     --*                           \n"
          "                   **---#@@##**++#%%**+++=-   #++-                           \n"
          "                  =%+=:--:-*@@%%#**%%%#**===*##=                             \n"
          "                  *%*++#%#=:-+@@@@@%%%%%%#+=*%#+=                            \n"
          "                  #%#+%@@%*+==+#@%@@@@@@=====#%#                             \n"
          "                  %%#+*@@@%#**+*@@@@@*:--=--+%@%=-                           \n"
          "                 :%%#++%@@@@@%**#@%=:...:==+*%@@%.-..                        \n"
          "                 :%%%%%%@@@@@@@%*..:      :==@%@@@%*:                        \n"
          "                  %%%%%@%@@@@@+.:=-  %@@* . -@@@@@@@#+.                      \n"
          "                  ##%%#**+++**#**+  .%@#: :.%#+%%%@@#%*=                     \n"
          "                  :*#@@@@@@%##*+**.  =+*:=.-@%*%%%%#%@@#+:                   \n"
          "                       *-@%@@@@@@%#+==+*+- #%#%@%%*##%@@@*=                  \n"
          "                        =%*%%%@@@@@@%##*+-:@@@@@@#+@#++#%@%+                 \n"
          "                         =#%%%@%*+#@@%#*+=*%@@@%#+%*%*-++#%%+                \n"
          "                          =#*%%%%%%%%%#*++#%#**%@%+=+#*===+%@+               \n"
          "                           =@**#%%%%%%%#+*%%#%%@@@@%#+++===+#%-              \n"
          "                           *@@@%##**###%@@@@%***#%@@%+*%+====#%.             \n"
          "                          .%%%%%@@@@@@@@@@@@@#*++**@@%+##====+##             \n"
          "                          ##*%*#%@@@@@@@@@@@@@%*+++*%@#*%*====+%-            \n"
          "                        .+%#%#*#%%@@@%%%@@@@@@@%*+=++%%#*%+====##            \n"
          "                       :-%#=*#**@@@@%%%#%@@@@@@@%#+=+*%%*#*====+%            \n"
          "                        =++*#*=:=##%@%#+*@@@@@@@@%#+++*@%*%+===+%-           \n"
          "                        %%%#%#*++ +%%%#*%%%@@@@@@@@%*++#@#%*====%+           \n"
          "                       -#%#%*%%#   +@%%#+++%%%%@@@@@@%**#@%+-===#+           \n"
          "                       #+##+%%+       +-#+=+%%%%%@@@@@@%#%.     #*.          \n"
          "                     -@%*#%+-+        :  +****++**#@@@@@@%       +.          \n"
          "                  :#@@#**%@@:                      %%##%##+      +.          \n"
          "                 =*@%@@@@@@+::                     #@@@@@**      =           \n"
          "               :%%%@@@@@@@                         *@@@@@.%-                 \n"
          "               =@%*@@@@@*                          :#%@#=%@*                 \n"
          "              --*+@@*@@+                            @@@@@@@.                 \n"
          "              %@@@@#@+                               @@@@@@                  \n"
          "             +@@@@@@:                                +@@@%@%                 \n"
          "             @@@@@+                                   @@@@@*                 \n"
          "            @@@@@.                                     @@@@@                 \n"
          "           *@@@@#                                      =@@@%                 \n"
          "           %*+:=                                       *@@%#*                \n"
          "          %@-+.-                                       @@@%*++               \n"
          "         @%*+:.:                                      .@@@@@#*.              \n"
          "         #@#*#*                                       .#%@@@@@#=.            \n"
          "                                                            .*@@@@@.         \n"
          "                                                                             \n";
}

// Pre-condition: called to display treasure art
// Post-condition: displays art
void treasureArt()
{
  cout << "*******************************************************************************\n"
          "          |                   |                  |                     |\n"
          " _________|________________.=\"\"_;=.______________|_____________________|_______\n"
          "|                   |  ,-\"_,=\"\"     `\"=.|                  |\n"
          "|___________________|__\"=._o`\"-._        `\"=.______________|___________________\n"
          "          |                `\"=._o`\"=._      _`\"=._                     |\n"
          " _________|_____________________:=._o \"=._.\"_.-=\"'\"=.__________________|_______\n"
          "|                   |    __.--\" , ; `\"=._o.\" ,-\"\"\"-._ \".   |\n"
          "|___________________|_._\"  ,. .` ` `` ,  `\"-._\"-._   \". '__|___________________\n"
          "          |           |o`\"=._` , \"` `; .\". ,  \"-._\"-._; ;              |\n"
          " _________|___________| ;`-.o`\"=._; .\" ` '`.\"\\` . \"-._ /_______________|_______\n"
          "|                   | |o;    `\"-.o`\"=._``  '` \" ,__.--o;   |\n"
          "|___________________|_| ;     (#) `-.o `\"=.`_.--\"_o.-; ;___|___________________\n"
          "____/______/______/___|o;._    \"      `\".o|o_.--\"    ;o;____/______/______/____\n"
          "/______/______/______/_\"=._o--._        ; | ;        ; ;/______/______/______/_\n"
          "____/______/______/______/__\"=._o--._   ;o|o;     _._;o;____/______/______/____\n"
          "/______/______/______/______/____\"=._o._; | ;_.--\"o.--\"_/______/______/______/_\n"
          "____/______/______/______/______/_____\"=.o|o_.--\"\"___/______/______/______/____\n"
          "/______/______/______/______/______/______/______/______/______/______/______/_\n"
          "*******************************************************************************\n\n";
}

// Pre-condition: called to display merchant art
// Post-condition: displays art
void merchantArt()
{
  cout << "             _.-;-._\n"
          "            ;_.JL___; \n"
          "            F\"-/\\_-7L\n"
          "            | a/ e | \\\n"
          "           ,L,c;,.='/;,\n"
          "        _,-;;S:;:S;;:' '--._\n"
          "       ;. \\;;s:::s;;: .'   /\\\n"
          "      /  \\  ;::::;;  /    /  \\\n"
          "     / ,  k ;S';;'S.'    j __,l\n"
          "  ,---/| /  /S   /S '.   |'   ;\n"
          " ,Ljjj |/|.' s .' s   \\  L    |\n"
          " LL,_ ]( \\    /    '.  '.||   ;\n"
          " ||\\ > /  ;-.'_.-.___\\.-'(|==\"(\n"
          " JJ,\" /   |_  [   ]     _]|   /\n"
          "  LL\\/   ,' '--'-'-----'  \\  ( \n"
          "  ||     ;      |          |  >\n"
          "  JJ     |      |\\         |,/\n"
          "   LL    |      ||       ' | \n"
          "   ||    |      ||       . |\n"
          "   JJ    /_     ||       ;_|\n"
          "    LL   L \"==='|i======='_|\n"
          "    ||    i----' '-------';\n"
          "    JJ    ';-----.------,-'\n"
          "     LL     L_.__J,'---;'\n"
          "     ||      |   ,|    (\n"
          "     JJ     .'=  (|  ,_|\n"
          "      LL   /    .'L_    \\\n"
          "      ||   '---'    '.___>\n\n";
}

// Pre-condition: called to display exit/door art
// Post-condition: displays art
void doorArt()
{
  cout << "88888888888888888888888888888888888888888888888888888888888888888888888\n"
          "88.._|      | `-.  | `.  -_-_ _-_  _-  _- -_ -  .'|   |.'|     |  _..88\n"
          "88   `-.._  |    |`!  |`.  -_ -__ -_ _- _-_-  .'  |.;'   |   _.!-'|  88\n"
          "88      | `-!._  |  `;!  ;. _______________ ,'| .-' |   _!.i'     |  88\n"
          "88..__  |     |`-!._ | `.| |_______________||.\"'|  _!.;'   |     _|..88\n"
          "88   |``\"..__ |    |`\";.| i|_|MMMMMMMMMMM|_|'| _!-|   |   _|..-|'    88\n"
          "88   |      |``--..|_ | `;!|l|MMoMMMMoMMM|1|.'j   |_..!-'|     |     88\n"
          "88   |      |    |   |`-,!_|_|MMMMP'YMMMM|_||.!-;'  |    |     |     88\n"
          "88___|______|____!.,.!,.!,!|d|MMMo * loMM|p|,!,.!.,.!..__|_____|_____88\n"
          "88      |     |    |  |  | |_|MMMMb,dMMMM|_|| |   |   |    |      |  88\n"
          "88      |     |    |..!-;'i|r|MPYMoMMMMoM|r| |`-..|   |    |      |  88\n"
          "88      |    _!.-j'  | _!,\"|_|M<>MMMMoMMM|_||!._|  `i-!.._ |      |  88\n"
          "88     _!.-'|    | _.\"|  !;|1|MbdMMoMMMMM|l|`.| `-._|    |``-.._  |  88\n"
          "88..-i'     |  _.''|  !-| !|_|MMMoMMMMoMM|_|.|`-. | ``._ |     |``\"..88\n"
          "88   |      |.|    |.|  !| |u|MoMMMMoMMMM|n||`. |`!   | `\".    |     88\n"
          "88   |  _.-'  |  .'  |.' |/|_|MMMMoMMMMoM|_|! |`!  `,.|    |-._|     88\n"
          "88  _!\"'|     !.'|  .'| .'|[@]MMMMMMMMMMM[@] \\|  `. | `._  |   `-._  88\n"
          "88-'    |   .'   |.|  |/| /                 \\|`.  |`!    |.|      |`-88\n"
          "88      |_.'|   .' | .' |/                   \\  \\ |  `.  | `._-  |   88\n"
          "88     .'   | .'   |/|  /                     \\ |`!   |`.|    `.  |  88\n"
          "88  _.'     !'|   .' | /                       \\|  `  |  `.    |`.|  88\n"
          "88888888888888888888888888888888888888888888888888888888888888888888888\n\n";

  // Pause the game until the user is ready
  cout << "Press enter to leave the dungeon: ";
  string enterKey = " ";
  getline(cin, enterKey);
  cout << "\n";
}

// Pre-condition: called to display victory art
// Post-condition: displays art with roomCount displayed
void victoryArt(int roomCount)
{
  cout << "     _______________________________________________________\n"
          "    /\\                                                      \\\n"
          "(O)===)><><><><><><><><><><><><><><><><><><><><><><><><><><><)==(O)\n"
          "    \\/''''''''''''''''''''''''''''''''''''''''''''''''''''''/\n"
          "    (                                                      (\n"
          "     )                                                      )\n"
          "    (                                                      (\n"
          "     )                                                      )\n"
          "\n"
          "    (                                                      (\n"
          "     )                                                      )\n"
          "    (                                                      (\n"
          "     )               Congratulations! You Win :)            )\n"
          "                            Room Count: " << roomCount << "\n"
          "    (                                                      (\n"
          "     )                                                      )\n"
          "    (                                                      (\n"
          "     )                                                      )\n"
          "\n"
          "    (                                                      (\n"
          "     )                                                      )\n"
          "    (                                                      (\n"
          "    /\\''''''''''''''''''''''''''''''''''''''''''''''''''''''\\    \n"
          "(O)===)><><><><><><><><><><><><><><><><><><><><><><><><><><><)==(O)\n"
          "    \\/______________________________________________________/\n\n";
}

// Pre-condition: called to display game over art
// Post-condition: displays art with roomCount displayed
void gameOverArt(int roomCount)
{
  cout << "   ______________________________\n"
          " / \\                             \\.\n"
          "|   |                            |.\n"
          " \\_ |                            |.\n"
          "    |                            |.\n"
          "    |                            |.\n"
          "    |                            |.\n"
          "    |                            |.\n"
          "    |          Game Over!        |.\n"
          "    |          Room Count: " << roomCount << setw(6 - (std::to_string(roomCount)).length()) << " " << "|.\n"
          "    |                            |.\n"
          "    |                            |.\n"
          "    |                            |.\n"
          "    |                            |.\n"
          "    |                            |.\n"
          "    |   _________________________|___\n"
          "    |  /                            /.\n"
          "    \\_/dc__________________________/.\n\n";
}

// Pre-condition: called to display tutorial
// Post-condition: displays tutorial
void tutorialGame()
{
  cout << ".-------------------------------------------------------------.\n"
       << "|                                                             |\n"
       << "|                      Game Information                       |\n"
       << "|                                                             |\n"
       << "|     Dastardly Dungeon Dwellers follows the story of         |\n"
       << "|     three brave adventures. You've entered this dungeon in  |\n"
       << "|     search of glory and riches beyond your desires.         |\n"
       << "|                                                             |\n"
       << "|     Only the courageous prevail, this dungeon is crawling   |\n"
       << "|     with baddies. If you're lucky, you'll encounter a       |\n"
       << "|     friendly traveling merchant to aid in your exploits.    |\n"
       << "|                                                             |\n"
       << "|     Scour the dungeon for its valuables, and defeat         |\n"
       << "|     its fearsome protector, if you feel capable.            |\n"
       << "|     Once you find the Golden Key, you can exit the          |\n"
       << "|     dungeon with your riches. Be warned, a powerful         |\n"
       << "|     foe hopes to exploit your hybris.                       |\n"
       << "|                                                             |\n"
       << "'-------------------------------------------------------------'\n";

  cout << "\n\tPress enter to return to the main menu: ";
  string enterKey = " ";
  getline(cin, enterKey);
}

// Pre-condition: called to display tutorial
// Post-condition: displays tutorial
void tutorialBattle()
{
  cout << ".-------------------------------------------------------------.\n"
       << "|                                                             |\n"
       << "|                     Battle Information                      |\n"
       << "|                                                             |\n"
       << "|       1. Melee Attack         4. Consume a potion           |\n"
       << "|       2. Magic Attack         5. Attempt to run away        |\n"
       << "|       3. Ranged Attack                                      |\n"
       << "|                                                             |\n"
       << "|     Damage values scale based on class selection and        |\n"
       << "|     enemy type. For example, skeletons take much more       |\n"
       << "|     damage from Melee damage rather than Ranged damage.     |\n"
       << "|                                                             |\n"
       << "|     Melee attacks deal moderate damage overall, but         |\n"
       << "|     may perform very poorly against certain enemies.        |\n"
       << "|                                                             |\n"
       << "|     Magic attacks deal varied damage depending on           |\n"
       << "|     enemy type, and Magic has a higher chance to deal       |\n"
       << "|     critical damage.                                        |\n"
       << "|                                                             |\n"
       << "|     Ranged attacks deal a high amount of damage, but        |\n"
       << "|     they have a chance to miss.                             |\n"
       << "|                                                             |\n"
       << "|     Potions are finite and heal for a random amount,        |\n"
       << "|     you can acquire more potions in the dungeon.            |\n"
       << "|                                                             |\n"
       << "|     If a fight seems insurmountable, you can always         |\n"
       << "|     run away. Be careful though, there's a chance you'll    |\n"
       << "|     fail to get away!                                       |\n"
       << "|                                                             |\n"
       << "'-------------------------------------------------------------'\n";

  cout << "\n\tPress enter to return to the game: ";
  string enterKey = " ";
  getline(cin, enterKey);
  cout << "\n";
}