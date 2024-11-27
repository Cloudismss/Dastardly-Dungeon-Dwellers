set(Sources
        # Sources
        "Enemy/Enemy Spawner.cpp"
        "Enemy/Enemy.cpp"
        "Enemy/Loot.cpp"
        "Enemy/Troll.cpp"
        "Player/Characters/Archer.cpp"
        "Player/Characters/Bard.cpp"
        "Player/Characters/Character.cpp"
        "Player/Characters/Mage.cpp"
        "Player/Characters/Warrior.cpp"
        "Player/Character List.cpp"
        "Player/Inventory.cpp"
        "Player/Player.cpp"
        "Room Controller/Room Controller.cpp"
        "Room Controller/Room Enemy.cpp"
        "Room Controller/Room Exit.cpp"
        "Room Controller/Room Loot.cpp"
        "Room Controller/Room Merchant.cpp"
        "Art.cpp"
        "Battle Controller.cpp"
        "Game.cpp"
        "Map.cpp"
        "Validation.cpp"
)

set(Dirs
        "../include"
        "../include/Enemy"
        "../include/Player"
        "../include/Player/Characters"
        "../include/Room Controller"
        "../lib/fmt/include"
)

add_library(src ${Sources})
target_include_directories(src PUBLIC ${Dirs})
