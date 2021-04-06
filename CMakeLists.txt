cmake_minimum_required(VERSION 3.17)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 20)

add_executable(TicTacToe main.cpp GameEvent.h GameManager.h ConsoleWriter.h DisplayWriter.h Coordinate.h Direction.h GameSession.h)