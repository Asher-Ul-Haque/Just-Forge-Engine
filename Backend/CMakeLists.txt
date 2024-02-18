cmake_minimum_required(VERSION 3.26)
project(Backend)

set(CMAKE_CXX_STANDARD 17)

add_library(Backend SHARED
        Components.h
        Entity.h
        Vector2D.h
        Vector2D.cpp
        GameEngine.cpp
        GameEngine.h
        EntityManager.h
        EntityManager.cpp
        Components.cpp
)



set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SuperMario/SFML/include/SFML)
target_link_libraries(Backend sfml-system sfml-window sfml-graphics sfml-audio)
