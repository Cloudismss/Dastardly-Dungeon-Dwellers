set(Includes
        # Main
        "../docs/Test.h"

        # Header Only
        "Globals.h"

        # Headers
        "Art.h"
        "Main Menu.h"
        "Map.h"
        "Validation.h"
        "Battle Controller.h"
        "Enemy/Enemy.h"
        "Enemy/Loot.h"
        "Game.h"
        "Player/Player.h"
        "Player/Characters.h"
        "Player/Skills.h"
        "Player/Inventory.h"
        "Room Controller/Room Controller.h"
        "Room Controller/Room Enemy.h"
        "Room Controller/Room Exit.h"
        "Room Controller/Room Loot.h"
        "Room Controller/Room Merchant.h"
)

add_library(include INTERFACE ${Includes})
