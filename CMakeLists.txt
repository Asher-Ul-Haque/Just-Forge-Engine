cmake_minimum_required(VERSION 3.26)
project(SuperMario)

set(CMAKE_CXX_STANDARD 17)
add_executable(SuperMario
        Engine/Vector2D.h
        Engine/Animation.h
        Engine/Assets.h
        Engine/Action.h
        Engine/Components.h
        Engine/Entity.h
        Engine/EntityManager.h
        Engine/Scene.h
        Engine/GameEngine.h
        Engine/SceneMenu.h
        Engine/Physics.h
        Engine/ScenePlay.h
        Engine/Vector2D.cpp
        Engine/Animation.cpp
        Engine/Assets.cpp
        Engine/Action.cpp
        Engine/EntityManager.cpp
        Engine/Physics.cpp
        Engine/SceneMenu.cpp
        Engine/GameEngine.cpp
        Engine/ScenePlay.cpp
        main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SuperMario/SFML/include/SFML)
target_link_libraries(SuperMario sfml-system sfml-window sfml-graphics sfml-audio)