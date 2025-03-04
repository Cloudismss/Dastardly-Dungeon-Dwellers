set(Includes
        # Header Only
        "Globals.h"

        # Headers
        "Enemy/Enemies/Boss.h"
        "Enemy/Enemies/Cyclops.h"
        "Enemy/Enemies/Enemy.h"
        "Enemy/Enemies/Goblin.h"
        "Enemy/Enemies/Minotaur.h"
        "Enemy/Enemies/Orc.h"
        "Enemy/Enemies/Skeleton.h"
        "Enemy/Enemies/Troll.h"
        "Enemy/EnemySpawner.h"
        "Enemy/Loot.h"
        "Player/Characters/Archer.h"
        "Player/Characters/Bard.h"
        "Player/Characters/Character.h"
        "Player/Characters/Mage.h"
        "Player/Characters/Warrior.h"
        "Player/CharacterList.h"
        "Player/Inventory.h"
        "Player/Player.h" 
        "RoomController/RoomController.h"
        "RoomController/RoomEnemy.h"
        "RoomController/RoomExit.h"
        "RoomController/RoomLoot.h"
        "RoomController/RoomMerchant.h"
        "Art.h"
        "BattleController.h"
        "Game.h"
        "Map.h"
        "Validation.h"
)

add_library(include INTERFACE ${Includes})
