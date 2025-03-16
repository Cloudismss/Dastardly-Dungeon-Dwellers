#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"

class Game
{
public:
  Game() { start(); }
  ~Game() { end(); }

private:
  void start();
  void end();
  void mainMenu();

public:
  static bool getDebug() { return debug; }

public:
  void loop();

private:
  // Debug toggle - displays useful debug information in the console and gives resources / increased damage
  static inline bool debug = false; // Enter -37 at the main menu to enter debug mode

private:
  Player *player;
  Map *map;

public:
  static inline bool winCondition;
  static inline bool running = true;
};

#endif // GAME_H
