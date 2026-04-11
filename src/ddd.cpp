#include "Game.h"

int main()
{
  Game ddd;
  while (ddd.running)
  {
    ddd.loop();
  }
}
