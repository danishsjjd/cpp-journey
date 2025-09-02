cmake_minimum_required(VERSION 4.1)

project(task-cli CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add_executable(task-cli src/main.cpp src/TaskManager.cpp)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(task-cli ${SOURCES})
