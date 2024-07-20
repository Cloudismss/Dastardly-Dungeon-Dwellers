set(Includes
        # Header Only
        "Globals.h"

        # Headers
        "Art.h"
        "Main Menu.h"
        "Map.h"
        "Validation.h"
        "Battle Controller/Battle Controller.h"
        #"Enemy/Boss.h"
        "Enemy/Enemy.h"
        "Enemy/Loot.h"
        #"Enemy/Troll.h"
        "Player/Player.h"
        "Player/Skills.h"
        "Room Controller/Room Controller.h"
        "Room Controller/Room Enemy.h"
        "Room Controller/Room Exit.h"
        "Room Controller/Room Loot.h"
        "Room Controller/Room Merchant.h"
)

add_library(include INTERFACE ${Includes})