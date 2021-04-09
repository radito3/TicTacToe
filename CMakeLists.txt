cmake_minimum_required(VERSION 3.17)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 20)

add_executable(TicTacToe main.cpp GameEvent.h GameEventQueue.h ConsoleWriter.h DisplayWriter.h Coordinate.h Direction.h GameSession.h AsciiEscapeCodes.h Player.h MatrixCell.h PlayerMovePlaceholderEvent.h WritePlayerSymbolEvent.h WriteMatrixEvent.h GameEventType.h InputReader.h ConsoleReader.h DisplayWriterWorker.h EventDispatcher.h InputReaderWorker.h Worker.h GameEndConditionChecker.h)