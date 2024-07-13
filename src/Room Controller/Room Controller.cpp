#include "Room Controller.h"

// Pre-condition: called by startGame() in a loop, passed className, inventory variables, game win/lose variables, map arrays and pointers, and characterStats file stream
// Post-condition: a room is selected within roomController, and game win/lose variables are updated based on result of room. The game ends if the game is won or lost
void roomController(string &className, int &potionCount, int &armorCount, int &goldCount, int &keyCount, int &roomCount, bool &gameOver, bool &gameVictory, char mapArray[MAP_ROWS][MAP_COLUMNS], bool roomExplored[MAP_ROWS][MAP_COLUMNS], string roomContents[MAP_ROWS][MAP_COLUMNS], char *&playerPosition, bool *&exploredPosition, string *&contentsPosition, std::ifstream &characterStats)
{
  static int enemyProgression;
  // map() allows the player to move between rooms. It returns false if the room has not been explored yet
  if (!(map(mapArray, roomExplored, roomContents, playerPosition, exploredPosition, contentsPosition)))
  {
    if (*contentsPosition == "Enemy")
    {
      roomEnemyMonologue();
      if (!roomEnemy(className, potionCount, armorCount, goldCount, keyCount, roomCount, characterStats))
      {
        gameOver = true;
        return;
      }
      ++roomCount;
      ++enemyProgression;
    }
    else if (*contentsPosition == "Loot")
    {
      bool isEnemyRoom = false;
      roomLootMonologue();
      treasureArt();
      if(!roomLoot(className, potionCount, armorCount, goldCount, keyCount, roomCount, isEnemyRoom, characterStats))
      {
        gameOver = true;
        return;
      }
      ++roomCount;
      if (isEnemyRoom)
      {
        ++enemyProgression;
      }
    }
    else if (*contentsPosition == "Merchant")
    {
      roomMerchantMonologue();
      merchantArt();
      roomMerchant(potionCount, armorCount, goldCount, keyCount, className);
      ++roomCount;
    }
    else if (*contentsPosition == "Exit")
    {
      roomExitMonologue();
      doorArt();
      roomExit(keyCount, gameVictory);
      ++roomCount;
    }
  }

  // This branch runs if the room has already been explored
  else
  {
    // Set dialogue switch to -1, so it runs room cleared dialogue
    int dialogueSwitch = -1;
    if (*contentsPosition == "Enemy")
    {
      monologueInABox("A powerful foe once inhabited this room");
      if (1 + (rand() % 100) <= 50)
      {
        roomEnemyMonologue(dialogueSwitch);
        if (!roomEnemy(className, potionCount, armorCount, goldCount, keyCount, roomCount, characterStats))
        {
          gameOver = true;
          return;
        }
        ++enemyProgression;
      }
    }
    else if (*contentsPosition == "Loot")
    {
      monologueInABox("A chest used to sit before me in this room");
      if (1 + (rand() % 100) <= 50)
      {
        roomLootMonologue(dialogueSwitch);
        if (!roomEnemy(className, potionCount, armorCount, goldCount, keyCount, roomCount, characterStats))
        {
          gameOver = true;
          return;
        }
        ++enemyProgression;
      }
    }
    else if (*contentsPosition == "Merchant")
    {
      monologueInABox("A friendly traveling merchant resides here");
      roomMerchantMonologue(dialogueSwitch);
      merchantArt();
      roomMerchant(potionCount, armorCount, goldCount, keyCount, className);
    }
    else if (*contentsPosition == "Exit")
    {
      monologueInABox("A strange sensation controls my actions");
      roomExitMonologue(dialogueSwitch);
      doorArt();
      roomExit(keyCount, gameVictory);
    }
    else if (*contentsPosition == "Start")
    {
      monologueInABox("This room seems familiar... have I gone in a circle???");
    }
  }

  // Display text indicating the enemy spawner has become more challenging
  static bool sayOnce1 = false, sayOnce2 = true, sayOnce3 = true;
  if (enemyProgression == 5)
  {
    if (!sayOnce1)
    {
      monologueInABox("Stronger foes have emerged from the depths of the dungeon...");
      sayOnce1 = true;
      sayOnce2 = false;
    }
  }
  if (enemyProgression == 10)
  {
    if (!sayOnce2)
    {
      monologueInABox("Stronger foes have emerged from the depths of the dungeon...");
      sayOnce2 = true;
      sayOnce3 = false;
    }
  }
  if (enemyProgression == 15)
  {
    if (!sayOnce3)
    {
      monologueInABox("Stronger foes have emerged from the depths of the dungeon...");
      sayOnce3 = true;
    }
  }
}