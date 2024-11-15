#include "Dastardly Dungeon Dwellers.h"

#include "Game.h"

int main()
{
  Game DDD;
  while(DDD.running())
  {
    DDD.progress();
  }
}
