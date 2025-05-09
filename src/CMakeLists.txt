set(Sources
        # Sources
        "Art/BattleArt.cpp"
        "Art/BoxArt.cpp"
        "Art/CharacterArt.cpp"
        "Art/DialogueArt.cpp"
        "Art/GameArt.cpp"
        "Art/RoomArt.cpp"
        "Art/TutorialArt.cpp"
        "Enemy/Enemies/Boss.cpp"
        "Enemy/Enemies/Cyclops.cpp"
        "Enemy/Enemies/Enemy.cpp"
        "Enemy/Enemies/Goblin.cpp"
        "Enemy/Enemies/Minotaur.cpp"
        "Enemy/Enemies/Orc.cpp"
        "Enemy/Enemies/Skeleton.cpp"
        "Enemy/Enemies/Troll.cpp"
        "Enemy/EnemySpawner.cpp"
        "Enemy/Loot.cpp"
        "Player/Characters/Archer.cpp"
        "Player/Characters/Bard.cpp"
        "Player/Characters/Character.cpp"
        "Player/Characters/Mage.cpp"
        "Player/Characters/Warrior.cpp"
        "Player/CharacterList.cpp"
        "Player/Inventory.cpp"
        "Player/Player.cpp"
        "RoomController/RoomController.cpp"
        "RoomController/RoomEnemy.cpp"
        "RoomController/RoomExit.cpp"
        "RoomController/RoomLoot.cpp"
        "RoomController/RoomMerchant.cpp"
        "BattleController.cpp"
        "Game.cpp"
        "Map.cpp"
        "Validation.cpp"
)

set(Dirs
        "../include"
        "../include/Art"
        "../include/Enemy"
        "../include/Enemy/Enemies"
        "../include/Player"
        "../include/Player/Characters"
        "../include/RoomController"
)

add_library(src ${Sources})
target_include_directories(src PUBLIC ${Dirs})
