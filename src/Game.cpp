#include "Game.h"

#include <iostream>
#include <string>

#include "GameArt.h"
#include "TutorialArt.h"

#include "RoomController.h"
#include "Validation.h"

void Game::start()
{
  // Seed the random number generator
  std::srand(std::time(nullptr));

  // I use a rand() here because the first value generated by rand() after srand() seems to be consistently increasing if the rand() bounds are large enough
  std::rand(); // rand range formula: min + (rand() % ((max + 1) - min))

  mainMenu();

  player = new Player;
  map = new Map;
}

void Game::end()
{
  // Print game results
  if (winCondition)
    art::game::victory(player);
  else
    art::game::gameOver(player);

  // Free memory
  delete player;
  delete map;

  // Pause the end screen until the user is ready to close the application
  std::cout << "Press enter to exit the program: ";
  std::string enterKey;
  getline(std::cin, enterKey);
  std::cout << "\n";
}

void Game::mainMenu()
{
  bool loopFlag = true;
  do
  {
    art::game::menu();
    int selection;
    std::cin >> selection;
    if (validate::input(selection, 1, 2))
    {
      if (selection == 1)
        loopFlag = false;
      else if (selection == 2)
      {
        art::tutorial::tutorialGame();
        std::cout << "\n";
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
