set(Sources
        # Sources
        "Art.cpp"
        "Main Menu.cpp"
        "Map.cpp"
        "Validation.cpp"
        "Battle Controller.cpp"
        "Enemy/Enemy.cpp"
        "Enemy/Loot.cpp"
        "Player/Player.cpp"
        "Player/Characters.cpp"
        "Player/Skills.cpp"
        "Room Controller/Room Controller.cpp"
        "Room Controller/Room Enemy.cpp"
        "Room Controller/Room Exit.cpp"
        "Room Controller/Room Loot.cpp"
        "Room Controller/Room Merchant.cpp"
)

set(Dirs
        "../include"
        "../include/Enemy"
        "../include/Player"
        "../include/Room Controller"
        "../lib/fmt/include"
)

add_library(src ${Sources})
target_include_directories(src PUBLIC ${Dirs})