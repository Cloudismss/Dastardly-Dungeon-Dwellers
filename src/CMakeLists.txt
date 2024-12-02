set(Sources
        # Sources
        "Enemy/Enemies/Boss.cpp"
        "Enemy/Enemies/Cyclops.cpp"
        "Enemy/Enemies/Enemy.cpp"
        "Enemy/Enemies/Goblin.cpp"
        "Enemy/Enemies/Minotaur.cpp"
        "Enemy/Enemies/Orc.cpp"
        "Enemy/Enemies/Skeleton.cpp"
        "Enemy/Enemies/Troll.cpp"
        "Enemy/Enemy Spawner.cpp"
        "Enemy/Loot.cpp"
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
        "../include/Enemy/Enemies"
        "../include/Player"
        "../include/Player/Characters"
        "../include/Room Controller"
        "../lib/fmt/include"
)

add_library(src ${Sources})
target_include_directories(src PUBLIC ${Dirs})
