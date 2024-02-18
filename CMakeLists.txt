cmake_minimum_required(VERSION 3.26)
project(SuperMario)

set(CMAKE_CXX_STANDARD 17)
add_executable(SuperMario
        Backend/Action.h
        Backend/Animation.h
        Backend/Assets.h
        Backend/Components.h
        Backend/Entity.h
        Backend/EntityManager.h
        Backend/GameEngine.h
        Backend/Physics.h
        Backend/Scene.h
        Backend/SceneMenu.h
        Backend/ScenePlay.h
        Backend/Vector2D.h
        Backend/Vector2D.cpp
        Backend/ScenePlay.cpp
        Backend/Action.cpp
        Backend/EntityManager.cpp
        Backend/Animation.cpp
        Backend/Physics.cpp
        Backend/GameEngine.cpp
        Backend/Assets.cpp
        Backend/SceneMenu.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SuperMario/SFML/include/SFML)
target_link_libraries(SuperMario sfml-system sfml-window sfml-graphics sfml-audio)