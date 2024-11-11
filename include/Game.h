#ifndef DASTARDLY_DUNGEON_DWELLERS_GAME_H
#define DASTARDLY_DUNGEON_DWELLERS_GAME_H

#include "Map.h"
#include "Player.h"

class Game
{
private:
  // Debug toggle - displays useful debug information in the console and gives resources / increased damage
  inline static bool debug = false; // Enter -37 at the main menu to enter debug mode
public:
  static void toggleDebug() { debug = true; }
  static bool getDebug() { return debug; }

private:
  bool gameOver;
  bool gameVictory;
  Player *player;
  Map *map;
  void start();
  void end();

public:
  Game() { start(); }
  ~Game() { end(); }
  bool running();
  void progress();
};

#endif // DASTARDLY_DUNGEON_DWELLERS_GAME_H
