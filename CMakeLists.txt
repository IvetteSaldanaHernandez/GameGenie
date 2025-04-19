cmake_minimum_required(VERSION 3.10)
project(GameGenie)

set(CMAKE_CXX_STANDARD 17)

add_executable(GameGenie backend/main.cpp backend/games.cpp)
