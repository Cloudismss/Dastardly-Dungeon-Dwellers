#include "Game.h"

#include <iostream>
#include <string>

#include "Art.h"
#include "Room Controller.h"
#include "Validation.h"

using std::cin;
using std::cout;
using std::string;

void Game::start()
{
  // Seed the random number generator
  std::srand(std::time(nullptr));

  // I use a rand() here because the first value generated by rand() after srand() seems to be consistently increasing if the rand() bounds are large enough
  std::rand(); // rand range formula: min + (rand() % ((max + 1) - min))

  // Menu Art
  mainMenu();

  // These variables will be constantly tracked / updated while the game is played
  player = new Player;

  // Generates the map with rooms to traverse
  map = new Map;
}

void Game::end()
{
  // Print game results
  if (winCondition)
    victoryArt(player);
  else
    gameOverArt(player);

  // Free memory
  delete player;
  delete map;

  // Pause the end screen until the user is ready to close the application
  cout << "Press enter to exit the program: ";
  string enterKey = " ";
  getline(cin, enterKey);
  cout << "\n";
}

void Game::mainMenu()
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
            "|            1: Start Game           2: Info                  |\n"
            "|                                                             |\n"
            "'-------------------------------------------------------------'\n";
    int selection = 0;
    cin >> selection;
    if (validateInput(selection, 1, 2))
    {
      if (selection == 1)
        loopFlag = false;
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

void Game::loop()
{
  roomController(player, map);
}
