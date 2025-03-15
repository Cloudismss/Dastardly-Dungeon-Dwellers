#include "DialogueArt.h"

#include <iostream>

namespace art
{
  namespace room
  {
    void roomEnemyMonologue(bool ROOM_EXPLORED)
    {
      // Random dialogue selection
      int randomChoice = 1 + (rand() % 5);

      if (!ROOM_EXPLORED)
      {
        switch (randomChoice)
        {
          case 1:
            std::cout << "Something foul reeks beyond this door... \n";
            break;
          case 2:
            std::cout << "I feel the hairs on my arm stand up straight...\n";
            break;
          case 3:
            std::cout << "I've got a bad feeling about this...\n";
            break;
          case 4:
            std::cout << "What could possibly go wrong...\n";
            break;
          case 5:
            std::cout << "The creatures of the dungeon sense my presence...\n";
            break;
        }
      }

      else
      {
        switch (randomChoice)
        {
          case 1:
            std::cout << "This doesn't feel right... \n";
            break;
          case 2:
            std::cout << "I sense my previous victory has not cleansed this room of evil...\n";
            break;
          case 3:
            std::cout << "Something seems off...\n";
            break;
          case 4:
            std::cout << "What could it be...\n";
            break;
          case 5:
            std::cout << "I can't believe my eyes...\n";
            break;
        }
      }
    }

    void roomLootMonologue(bool ROOM_EXPLORED)
    {
      // Random dialogue selection
      int randomChoice = 1 + (rand() % 5);

      if (!ROOM_EXPLORED)
      {
        switch (randomChoice)
        {
          case 1:
            std::cout << "I notice a shimmering golden gleam between the cracks of this door...\n";
            break;
          case 2:
            std::cout << "What's this...\n";
            break;
          case 3:
            std::cout << "I've got a good feeling about this...\n";
            break;
          case 4:
            std::cout << "Do my eyes betray me...\n";
            break;
          case 5:
            std::cout << "I can't believe my eyes...\n";
            break;
        }
        std::cout << "A magnificent golden chest sits in the middle of the room!\n\n";
      }

      else
      {
        switch (randomChoice)
        {
          case 1:
            std::cout << "This doesn't feel right... \n";
            break;
          case 2:
            std::cout << "I sense my previous victory has not cleansed this room of evil...\n";
            break;
          case 3:
            std::cout << "Something seems off...\n";
            break;
          case 4:
            std::cout << "What could it be...\n";
            break;
          case 5:
            std::cout << "I can't believe my eyes...\n";
            break;
        }
        std::cout << "The chest magically refilled its contents!\n\n";
      }

    }

    void roomMerchantMonologue(bool ROOM_EXPLORED)
    {
      // Random dialogue selection
      int randomChoice = 1 + (rand() % 2);

      if (!ROOM_EXPLORED)
      {
        switch (randomChoice)
        {
          case 1:
            std::cout << "Welcome to my shop!\n";
            break;
          case 2:
            std::cout << "Greetings traveler!\n";
            break;
        }
        std::cout << "Take a gander upon my wares...\n\n";
      }

      else
      {
        switch (randomChoice)
        {
          case 1:
            std::cout << "Welcome back to my shop!\n";
            break;
          case 2:
            std::cout << "I'm glad to see you still in one piece!\n";
            break;
        }
        std::cout << "I've found more supplies since we've last met...\n\n";
      }
    }

    void roomExitMonologue(bool ROOM_EXPLORED)
    {
      // Random dialogue selection
      int randomChoice = 1 + (rand() % 5);

      if (!ROOM_EXPLORED)
      {
        switch (randomChoice)
        {
          default: // I haven't gotten around to writing more monologue yet
            std::cout << "You notice a strange door, unlike any you've seen before. You're not sure why, but you feel it calling to you...\n\n";
            break;
        }
      }

      else
      {
        switch (randomChoice)
        {
          default: // I haven't gotten around to writing more monologue yet
            std::cout << "You feel an overwhelming urge pulling you towards this room\n\n";
            break;
        }
      }
    }
  }
}
