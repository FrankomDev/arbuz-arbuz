cmake_minimum_required(VERSION 3.31)
set(PROJECT_NAME arbuz)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/fruit.cpp
        src/spawner.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
find_package(raylib REQUIRED)
find_package(box2d REQUIRED)

target_link_libraries(${PROJECT_NAME}
        raylib
        box2d
)


