#include "Art.h"

#include <iomanip>
#include <iostream>

#include "Validation.h"

using std::cout;
using std::cin;
using std::setfill;
using std::setw;

// Pre-condition: called by battleController(), passed player and enemy objects
// Post-condition: returns user selection from displayed battleMenu
string battleMenu(Player *player, Enemy *enemy)
{
  // Menu Variables
  int boxWidth = 63;
  int borderSpacing = ((boxWidth - 23) / 2);
  string choiceName[] = {player->getSkillName("Melee"), player->getSkillName("Magic"), player->getSkillName("Ranged")};

  short int battleMenuSelection = 0;
  bool loopFlag = true;
  do
  {
    battleHealthArt(player->getHealth(), enemy->getHealth());
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
        loopFlag = false;
      else
      {
        cout << "\n";
        tutorialBattle();
      }
    }
  } while (loopFlag);
  cout << "\n";

  if (battleMenuSelection == 1)
    return "Melee";
  else if (battleMenuSelection == 2)
    return "Magic";
  else if (battleMenuSelection == 3)
    return "Ranged";
  else if (battleMenuSelection == 4)
    return "Heal";
  else if (battleMenuSelection == 5)
    return "Run";

  // TODO: Implement clean fix for return in all control paths
  return "Error";
}

// Pre-condition: called by battleMenu(), passed health variables
// Post-condition: displays health art
void battleHealthArt(int playerHealth, int enemyHealth)
{
  // Don't print health if either the player or the enemy has 0 health
  if (playerHealth <= 0 || enemyHealth <= 0)
    return;

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

// Pre-condition: called to display text in a box. Ensure a newline is used prior to the call to this function, it can't be included here because of vaired implementaton
// Post-condition: displays text in a box based on string length
void displayMeInABox(const string &message)
{
  // Offsets are used to clean up integer division spacing
  int offset = 0;
  if (message.length() % 2 == 0)
    offset = 1;

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

// Pre-condition: called to display 2 lines of text in a box. Ensure a newline is used prior to the call to this function, it can't be included here because of vaired implementaton
// Post-condition: displays 2 lines of text in a box based on string length
void displayMeInABox(const string &message1, const string &message2)
{
  // Offsets are used to clean up integer division spacing
  int offset1 = 0;
  int offset2 = 0;
  if (message1.length() % 2 == 0)
    offset1 = 1;
  if (message2.length() % 2 == 0)
    offset2 = 1;

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
        cout << "You notice a strange door, unlike any you've seen before. You're not sure why, but you feel it calling to you...\n\n";
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
}

// Pre-condition: called to display victory art
// Post-condition: displays art with roomCount displayed
void victoryArt(Player *player)
{
  int roomCount = player->getRoomCount();
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
void gameOverArt(Player *player)
{
  int roomCount = player->getRoomCount();
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
