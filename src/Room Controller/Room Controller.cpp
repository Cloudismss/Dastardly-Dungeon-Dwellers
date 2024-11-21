#include "Room Controller.h"

#include "Art.h"
#include "Game.h"
#include "Globals.h"
#include "Room Enemy.h"
#include "Room Exit.h"
#include "Room Loot.h"
#include "Room Merchant.h"

// Pre-condition: called by startGame() in a loop, passed className, inventory variables, game win/lose variables, map arrays and pointers, and characterStats file stream
// Post-condition: a room is selected within roomController, and game win/lose variables are updated based on result of room. The game ends if the game is won or lost
void roomController(Player *player, Map *map)
{
  // map->move() allows the player to move between rooms. It returns false if the room has not been explored yet
  const bool ROOM_EXPLORED = map->move();
  const string ROOM_NAME = map->getRoomContents();

  // This variable is set to true if an enemy is encountered
  bool isEnemyRoom = false;

  if (ROOM_NAME == "Enemy")
  {
    if (ROOM_EXPLORED)
    {
      art::box::monologueInABox("A powerful foe once inhabited this room");
      
      // There is a 50% chance the room will respawn
      if (1 + (rand() % 100) <= 50)
        return; // Room did not respawn
    }
    else
      isEnemyRoom = true;

    art::room::roomEnemyMonologue(ROOM_EXPLORED);

    // Initiate enemy room
    if (!roomEnemy(player))
    {
      Game::winCondition = false;
      Game::running = false;
      return;
    }
  }

  else if (ROOM_NAME == "Loot")
  {
    if (ROOM_EXPLORED)
    {
      art::box::monologueInABox("A chest used to sit before me in this room");
      
      // There is a 50% chance the room will respawn
      if (1 + (rand() % 100) <= 50)
        return; // Room did not respawn
    }

    art::room::roomLootMonologue(ROOM_EXPLORED);
    art::room::treasureArt();
    
    // Initiate loot room
    if(!roomLoot(player, isEnemyRoom))
    {
      Game::winCondition = false;
      Game::running = false;
      return;
    }
  }

  else if (ROOM_NAME == "Merchant")
  {
    if (ROOM_EXPLORED)
      art::box::monologueInABox("A friendly traveling merchant resides here");

    art::room::roomMerchantMonologue(ROOM_EXPLORED);
    art::room::merchantArt();

    // Initiate merchant room
    roomMerchant(player);
  }

  else if (ROOM_NAME == "Exit")
  {
    if (ROOM_EXPLORED)
      art::box::monologueInABox("A strange sensation controls my actions");

    art::room::roomExitMonologue(ROOM_EXPLORED);
    art::room::doorArt();

    // Initiate exit room
    roomExit(player);

    if (Game::winCondition)
    {
      Game::running = false;
      return;
    }
  }
  
  else if (ROOM_NAME == "Start")
    art::box::monologueInABox("This room seems familiar... have I gone in a circle???");

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
          art::box::monologueInABox("Stronger foes have emerged from the depths of the dungeon...");
      player->progress();
    }

    // Increment room counter
    player->roomCleared();
  }
}
