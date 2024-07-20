#include "Room Controller.h"

// Pre-condition: called by startGame() in a loop, passed className, inventory variables, game win/lose variables, map arrays and pointers, and characterStats file stream
// Post-condition: a room is selected within roomController, and game win/lose variables are updated based on result of room. The game ends if the game is won or lost
void roomController(Player *player, Map *map, bool &gameOver, bool &gameVictory)
{
  // map->move() allows the player to move between rooms. It returns false if the room has not been explored yet
  const bool ROOM_EXPLORED = map->move();
  const string ROOM_NAME = map->getRoomContents();

  // Dialogue controller - determines which text should display when it comes to room explored vs not explored
  int dialogueSwitch = 0;

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

    roomEnemyMonologue(dialogueSwitch);

    // Initiate enemy room
    if (!roomEnemy(player))
    {
      gameOver = true;
      return;
    }
    player->progress();

    // Increment room count if this room was not explored previously
    if (!ROOM_EXPLORED)
      player->roomCleared();
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

    // This variable is set to true if a trap chest is discovered
    bool isEnemyRoom = false;

    roomLootMonologue(dialogueSwitch);
    treasureArt();
    
    // Initiate loot room
    if(!roomLoot(player, isEnemyRoom))
    {
      gameOver = true;
      return;
    }

    // Increment enemy progression if a trap chest battle was cleared
    if (isEnemyRoom)
      player->progress();

    // Increment room count if this room was not explored previously
    if (!ROOM_EXPLORED)
      player->roomCleared();
  }
  else if (ROOM_NAME == "Merchant")
  {
    if (ROOM_EXPLORED)
    {
      // Set dialogue switch to -1, so it runs room cleared dialogue
      dialogueSwitch = -1;
      monologueInABox("A friendly traveling merchant resides here");
      
      // There is a 50% chance the room will respawn
      if (1 + (rand() % 100) <= 50)
        return;
    }

    roomMerchantMonologue(dialogueSwitch);
    merchantArt();

    // Initiate merchant room
    roomMerchant(player);

    // Increment room count if this room was not explored previously
    if (!ROOM_EXPLORED)
      player->roomCleared();
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
    
    // Increment room count if this room was not explored previously
    if (!ROOM_EXPLORED)
      player->roomCleared();
  }
  else if (ROOM_NAME == "Start")
  {
    monologueInABox("This room seems familiar... have I gone in a circle???");
  }

  // Display text indicating the enemy spawner has become more challenging
  static bool checkpoint1 = false, checkpoint2 = true, checkpoint3 = true;
  if (player->getProgression() == 5)
  {
    if (!checkpoint1)
    {
      monologueInABox("Stronger foes have emerged from the depths of the dungeon...");
      checkpoint1 = true;
      checkpoint2 = false;
    }
  }
  if (player->getProgression() == 10)
  {
    if (!checkpoint2)
    {
      monologueInABox("Stronger foes have emerged from the depths of the dungeon...");
      checkpoint2 = true;
      checkpoint3 = false;
    }
  }
  if (player->getProgression() == 15)
  {
    if (!checkpoint3)
    {
      monologueInABox("Stronger foes have emerged from the depths of the dungeon...");
      checkpoint3 = true;
    }
  }
}