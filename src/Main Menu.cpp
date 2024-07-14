#include "Main Menu.h"

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
      // TODO: find new implementation
      //debug = true;
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