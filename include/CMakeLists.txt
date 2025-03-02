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
        "Room Controller/Room Controller.h"
        "Room Controller/Room Enemy.h"
        "Room Controller/Room Exit.h"
        "Room Controller/Room Loot.h"
        "Room Controller/Room Merchant.h"
        "Art.h"
        "Battle Controller.h"
        "Game.h"
        "Map.h"
        "Validation.h"
)

add_library(include INTERFACE ${Includes})
