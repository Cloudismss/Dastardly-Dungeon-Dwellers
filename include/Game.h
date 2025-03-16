#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"

class Game
{
private:
  // Debug toggle - displays useful debug information in the console and gives resources / increased damage
  static inline bool debug = false; // Enter -37 at the main menu to enter debug mode

public:
  static bool getDebug() { return debug; }

public:
  static inline bool winCondition;
  static inline bool running = true;

private:
  Player *player;
  Map *map;

private:
  void start();
  void end();
  void mainMenu();

public:
  Game() { start(); }
  ~Game() { end(); }
  void loop();
};

#endif // GAME_H
