#include "Main Menu.h"

#include <iostream>

#include "Art.h"
#include "Validation.h"

using std::cin;
using std::cout;

// Pre-condition: called by startGame() to print the menu screen
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
        loopFlag = false;
      else if (selection == 2)
      {
        tutorialGame();
        cout << "\n";
      }
    }
    else if (selection == -37) // Secret entry to activate debug mode
    {
      // TODO: find new implementation
      //debug = true;
      std::cerr << "Debug mode enabled\n\n";
    }
  } while (loopFlag);
}
