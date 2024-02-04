cmake_minimum_required(VERSION 3.26)
project(SpaceShooter)

set(CMAKE_CXX_STANDARD 17)
add_executable(SpaceShooter main.cpp
               Backend/Components.h
               Backend/Vector2D.h
               Backend/Entity.h
               Backend/Vector2D.cpp
               Backend/Game.h
        Backend/Game.cpp
        Backend/EntityManager.h
        Backend/EntityManager.cpp
        Backend/Components.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SpaceShooter/SFML/include/SFML)
target_link_libraries(SpaceShooter sfml-system sfml-window sfml-graphics sfml-audio)

add_subdirectory(Backend)
