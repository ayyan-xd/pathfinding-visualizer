cmake_minimum_required(VERSION 3.14)
project(PathfindingVisualizer)

set(CMAKE_CXX_STANDARD 17)

add_executable(pathfinder src/main.cpp)

target_include_directories(pathfinder PRIVATE ${CMAKE_SOURCE_DIR}/raylib/include)
target_link_libraries(pathfinder
    ${CMAKE_SOURCE_DIR}/raylib/lib/libraylib.a
    opengl32 gdi32 winmm)