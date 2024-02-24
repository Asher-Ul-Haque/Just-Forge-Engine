cmake_minimum_required(VERSION 3.26)
project(SuperMario)

set(CMAKE_CXX_STANDARD 17)
add_executable(SuperMario
        Engine/TheMachine/PhysicsEngine/Vector2D.h
        Engine/TheMachine/Management/Animation.h
        Engine/TheMachine/Management/Assets.h
        Engine/TheMachine/Management/Action.h
        Engine/TheMachine/Entities/Components.h
        Engine/TheMachine/Entities/Entity.h
        Engine/TheMachine/Entities/EntityManager.h
        Engine/TheMachine/Scenes/Scene.h
        Engine/TheMachine/GameEngine.h
        Engine/TheMachine/Scenes/SceneMenu.h
        Engine/TheMachine/PhysicsEngine/Physics.h
        Engine/TheMachine/Scenes/ScenePlay.h
        Engine/TheFuel/PhysicsEngine/Vector2D.cpp
        Engine/TheFuel/Management/Animation.cpp
        Engine/TheFuel/Management/Assets.cpp
        Engine/TheFuel/Management/Action.cpp
        Engine/TheFuel/Entities/EntityManager.cpp
        Engine/TheFuel/PhysicsEngine/Physics.cpp
        Engine/TheFuel/Scenes/SceneMenu.cpp
        Engine/TheFuel/GameEngine.cpp
        Engine/TheFuel/Scenes/ScenePlay.cpp
        SampleGame.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(SFML/lib/cmake/SFML)
target_link_libraries(SuperMario sfml-system sfml-window sfml-graphics sfml-audio)