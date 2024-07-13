cmake_minimum_required(VERSION 3.30.0)
project("Dastardly Dungeon Dwellers" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")

# Source Library
add_library
(
        src
        "src/Art.h"
        "src/Art.cpp"
        "src/Globals.h"
        "src/Main Menu.h"
        "src/Main Menu.cpp"
        "src/Map Generator.h"
        "src/Map Generator.cpp"
        "src/Map.h"
        "src/Map.cpp"
        "src/Progression.h"
        "src/Progression.cpp"
        "src/Validation.h"
        "src/Validation.cpp"
        "src/Battle Controller/Battle Controller.h"
        "src/Battle Controller/Battle Controller.cpp"
        "src/Battle Controller/Enemy Damage.h"
        "src/Battle Controller/Enemy Damage.cpp"
        "src/Battle Controller/Enemy Resistance.h"
        "src/Battle Controller/Enemy Resistance.cpp"
        "src/Battle Controller/Enemy Spawner.h"
        "src/Battle Controller/Enemy Spawner.cpp"
        "src/Battle Controller/Player Damage.h"
        "src/Battle Controller/Player Damage.cpp"
        "src/Enemy/Boss.h"
        "src/Enemy/Boss.cpp"
        "src/Enemy/Enemy.h"
        "src/Enemy/Enemy.cpp"
        "src/Enemy/Troll.h"
        "src/Enemy/Troll.cpp"
        "src/Player/Player.h"
        "src/Player/Player.cpp"
        "src/Player/Skills.h"
        "src/Player/Skills.cpp"
        "src/Player/Upgrade.h"
        "src/Player/Upgrade.cpp"
        "src/Room Controller/Room Controller.h"
        "src/Room Controller/Room Controller.cpp"
        "src/Room Controller/Room Enemy.h"
        "src/Room Controller/Room Enemy.cpp"
        "src/Room Controller/Room Exit.h"
        "src/Room Controller/Room Exit.cpp"
        "src/Room Controller/Room Loot.h"
        "src/Room Controller/Room Loot.cpp"
        "src/Room Controller/Room Merchant.h"
        "src/Room Controller/Room Merchant.cpp"
)

add_executable("Dastardly Dungeon Dwellers" "Dastardly Dungeon Dwellers.cpp")

add_subdirectory(src)
target_link_libraries("Dastardly Dungeon Dwellers" PUBLIC src)
target_include_directories("Dastardly Dungeon Dwellers" PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src")
add_subdirectory_and_get_targets("src" SRC_TARGETS)
targets_set_warnings_as_errors(${SRC_TARGETS})