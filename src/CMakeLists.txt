set(Sources
        # Sources
        "Art.cpp"
        "Main Menu.cpp"
        "Map Generator.cpp"
        "Map.cpp"
        "Progression.cpp"
        "Validation.cpp"
        "Battle Controller/Battle Controller.cpp"
        "Battle Controller/Enemy Damage.cpp"
        "Battle Controller/Enemy Resistance.cpp"
        "Battle Controller/Enemy Spawner.cpp"
        "Battle Controller/Player Damage.cpp"
        #"Enemy/Boss.cpp"
        #"Enemy/Enemy.cpp"
        #"Enemy/Troll.cpp"
        "Player/Player.cpp"
        "Player/Skills.cpp"
        "Player/Upgrade.cpp"
        "Room Controller/Room Controller.cpp"
        "Room Controller/Room Enemy.cpp"
        "Room Controller/Room Exit.cpp"
        "Room Controller/Room Loot.cpp"
        "Room Controller/Room Merchant.cpp"
)

add_library(src ${Sources})

target_include_directories(src PUBLIC "../include")
target_include_directories(src PUBLIC "../include/Battle Controller")
target_include_directories(src PUBLIC "../include/Enemy")
target_include_directories(src PUBLIC "../include/Player")
target_include_directories(src PUBLIC "../include/Room Controller")