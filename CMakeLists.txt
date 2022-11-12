cmake_minimum_required(VERSION 3.21)
project(sudoku_solver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fconstexpr-ops-limit=1073741824 -Wall -Wpedantic -Werror")
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(C:/dev/cpp/lmj-misc/src) # directory for https://github.com/JonathanHallstrom/lmj-misc
add_executable(sudoku_solver main.cpp)
