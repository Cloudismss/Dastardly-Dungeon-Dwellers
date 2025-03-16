#include "GameArt.h"

#include <iomanip>
#include <iostream>

namespace art
{
  namespace game
  {
    void victoryArt(Player *player)
    {
      int roomCount = player->getRoomCount();
      std::cout << "     _______________________________________________________\n"
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

    void gameOverArt(Player *player)
    {
      int roomCount = player->getRoomCount();
      std::cout << "   ______________________________\n"
                   " / \\                             \\.\n"
                   "|   |                            |.\n"
                   " \\_ |                            |.\n"
                   "    |                            |.\n"
                   "    |                            |.\n"
                   "    |                            |.\n"
                   "    |                            |.\n"
                   "    |          Game Over!        |.\n"
                   "    |          Room Count: " << roomCount << std::setw(6 - (std::to_string(roomCount)).length()) << " " << "|.\n"
                   "    |                            |.\n"
                   "    |                            |.\n"
                   "    |                            |.\n"
                   "    |                            |.\n"
                   "    |                            |.\n"
                   "    |   _________________________|___\n"
                   "    |  /                            /.\n"
                   "    \\_/dc__________________________/.\n\n";
    }
  }
}