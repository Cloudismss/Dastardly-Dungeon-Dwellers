set(Includes
        # TEMP: Test Code
        "../docs/Test.h"

        # Header Only
        "Globals.h"

        # Headers
        "Enemy/Enemy.h"
        "Enemy/Loot.h"
        "Player/Characters/Archer.h"
        "Player/Characters/Bard.h"
        "Player/Characters/Character.h"
        "Player/Characters/Mage.h"
        "Player/Characters/Warrior.h"
        "Player/Character List.h"
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
        "Main Menu.h"
        "Map.h"
        "Validation.h"
)

add_library(include INTERFACE ${Includes})
