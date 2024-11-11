#include "Dastardly Dungeon Dwellers.h"

int main()
{
  Game DDD;
  while(DDD.running())
  {
    DDD.progress();
  }
}