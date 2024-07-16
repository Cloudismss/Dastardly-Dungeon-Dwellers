#include "Dastardly Dungeon Dwellers.h"

// BEGIN TESTING PROTOTYPES | FUNCTIONS | INCLUDES
// !
// TODO
// ?
// *

#include "fmt/base.h"
#include "fmt/color.h"

#include "boost/random/mersenne_twister.hpp"
#include "boost/random/uniform_int_distribution.hpp"
#include "boost/random/discrete_distribution.hpp"

// END TESTING PROTOTYPES | FUNCTIONS | INCLUDES

int main()
{
  // BEGIN TESTING CODE
  // !
  // TODO
  // ?
  // *

  // Print red text
  fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "Test\n");

  // Random number 1-100
  boost::random::mt19937 gen(std::time(nullptr));
  boost::random::uniform_int_distribution<> dist1(1, 100);
  cout << dist1(gen) << "\n";

  // Weighted probability 1-6
  double probabilities[] = {0.5, 0.1, 0.1, 0.1, 0.1, 0.1};
  boost::random::discrete_distribution<> dist2(probabilities);
  cout << dist2(gen) + 1 << "\n";

  cout << "\n\n\n\n";

  // END TESTING CODE
  
  std::srand(std::time(nullptr));

  // I use a rand() here because the first value generated by rand() after srand() seems to be consistently increasing if the rand() bounds are large enough
  std::rand(); // rand range formula: min + (rand() % ((max + 1) - min))

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