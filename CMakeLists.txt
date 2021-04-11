cmake_minimum_required(VERSION 3.17)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 20)

add_executable(TicTacToe main.cpp events/GameEvent.h GameEventQueue.h ConsoleWriter.h DisplayWriter.h Coordinate.h Direction.h GameSession.h AsciiEscapeCodes.h Player.h MatrixCell.h events/MovePlayerPlaceholderEvent.h events/WritePlayerSymbolEvent.h events/WriteMatrixEvent.h events/GameEventType.h InputReader.h ConsoleReader.h DisplayWriterWorker.h GamePlayerSwitcher.h InputReaderWorker.h Worker.h GameEndConditionChecker.h events/WritePlayerPlaceholderEvent.h events/GameSwitchPlayerEvent.h events/GameCheckEndConditionEvent.h)