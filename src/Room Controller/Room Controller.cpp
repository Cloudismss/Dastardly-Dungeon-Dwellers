#include "Room Controller.h"

#include "Globals.h"

#include "Art.h"
#include "Room Enemy.h"
#include "Room Exit.h"
#include "Room Loot.h"
#include "Room Merchant.h"

// Pre-condition: called by startGame() in a loop, passed className, inventory variables, game win/lose variables, map arrays and pointers, and characterStats file stream
// Post-condition: a room is selected within roomController, and game win/lose variables are updated based on result of room. The game ends if the game is won or lost
void roomController(Player *player, Map *map, bool &gameOver, bool &gameVictory)
{
  // map->move() allows the player to move between rooms. It returns false if the room has not been explored yet
  const bool ROOM_EXPLORED = map->move();
  const string ROOM_NAME = map->getRoomContents();

  // Dialogue controller - determines which text should display when it comes to room explored vs not explored
  int dialogueSwitch = 0;

  // This variable is set to true if an enemy is encountered
  bool isEnemyRoom = false;

  if (ROOM_NAME == "Enemy")
  {
    if (ROOM_EXPLORED)
    {
      // Set dialogue switch to -1, so it runs room cleared dialogue
      dialogueSwitch = -1;
      monologueInABox("A powerful foe once inhabited this room");
      
      // There is a 50% chance the room will respawn
      if (1 + (rand() % 100) <= 50)
        return;
    }
    else
      isEnemyRoom = true;

    roomEnemyMonologue(dialogueSwitch);

    // Initiate enemy room
    if (!roomEnemy(player))
    {
      gameOver = true;
      return;
    }
  }
  else if (ROOM_NAME == "Loot")
  {
    if (ROOM_EXPLORED)
    {
      // Set dialogue switch to -1, so it runs room cleared dialogue
      dialogueSwitch = -1;
      monologueInABox("A chest used to sit before me in this room");
      
      // There is a 50% chance the room will respawn
      if (1 + (rand() % 100) <= 50)
        return;
    }

    roomLootMonologue(dialogueSwitch);
    treasureArt();
    
    // Initiate loot room
    if(!roomLoot(player, isEnemyRoom))
    {
      gameOver = true;
      return;
    }
  }
  else if (ROOM_NAME == "Merchant")
  {
    if (ROOM_EXPLORED)
    {
      // Set dialogue switch to -1, so it runs room cleared dialogue
      dialogueSwitch = -1;
      monologueInABox("A friendly traveling merchant resides here");
    }

    roomMerchantMonologue(dialogueSwitch);
    merchantArt();

    // Initiate merchant room
    roomMerchant(player);
  }
  else if (ROOM_NAME == "Exit")
  {
    if (ROOM_EXPLORED)
    {
      // Set dialogue switch to -1, so it runs room cleared dialogue
      dialogueSwitch = -1;
      monologueInABox("A strange sensation controls my actions");
    }

    roomExitMonologue(dialogueSwitch);
    doorArt();

    // Initiate exit room
    roomExit(player, gameVictory);
  }
  else if (ROOM_NAME == "Start")
    monologueInABox("This room seems familiar... have I gone in a circle???");

  // Increment room count if this room was not explored previously
  if (!ROOM_EXPLORED)
  {
    // Increment enemy progression if an enemy was defeated
    if (isEnemyRoom)
    {
      // Display text indicating the enemy spawner has become more challenging
      short unsigned int progression = player->getProgression();
      if (progression + 1 == CHECKPOINT_1 ||
          progression + 1 == CHECKPOINT_2 ||
          progression + 1 == CHECKPOINT_3)
          monologueInABox("Stronger foes have emerged from the depths of the dungeon...");
      player->progress();
    }

    // Increment room counter
    player->roomCleared();
  }
}