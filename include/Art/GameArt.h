#ifndef GAMEART_H
#define GAMEART_H

#include "Player.h"

namespace art::game
{
void menu();
void classSelection();
void victory(Player *player);
void gameOver(Player *player);
} // namespace art::game

#endif // GAMEART_H
