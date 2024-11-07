cmake_minimum_required(VERSION 3.30.0)
project(Dastardly-Dungeon-Dwellers LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_HOST_WIN32)
  # Enable static compilation
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  # UTF-8 option is required when using fmt
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
else()
  # set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")
endif()

# Executable
add_executable(${PROJECT_NAME} "Dastardly Dungeon Dwellers.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Dastardly Dungeon Dwellers")

# Dirs
add_subdirectory(include)
add_subdirectory(src)
target_link_libraries(${PROJECT_NAME} include)
target_link_libraries(${PROJECT_NAME} src)

# fmt library
add_subdirectory(lib/fmt)
target_link_libraries(${PROJECT_NAME} fmt::fmt)

# boost library
#add_subdirectory(lib/boost EXCLUDE_FROM_ALL)
#target_link_libraries(${PROJECT_NAME} Boost::random)
