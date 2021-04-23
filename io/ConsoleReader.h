#ifndef TICTACTOE_CONSOLEREADER_H
#define TICTACTOE_CONSOLEREADER_H

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdio>
#include "InputReader.h"
#include "../AsciiEscapeCodes.h"

class ConsoleReader : public TimeoutInputReader {

    const int gitBashLineOffset = 4;

    static void move_cursor_to(int line, int column) {
        printf(AsciiEscapeCodes::MoveToPos, line, column);
    }

    static MoveDirection parse_move_direction(char ch) {
        switch (ch) {
            case 'w':
                return MoveDirection::UP;
            case 's':
                return MoveDirection::DOWN;
            case 'a':
                return MoveDirection::LEFT;
            case 'd':
                return MoveDirection::RIGHT;
            default:
                return MoveDirection::INVALID;
        }
    }

public:

    input_t read() const override {
        using namespace std::chrono_literals;
        move_cursor_to(gitBashLineOffset, 22);
        char ch;
        while (std::cin >> ch) {
            move_cursor_to(gitBashLineOffset, 22);
            if (ch == 'q') {
                return input_t(true);
            }
            MoveDirection move_dir = parse_move_direction(ch);
            if (move_dir != MoveDirection::INVALID) {
                return input_t(move_dir);
            }
            move_cursor_to(gitBashLineOffset, 22);
            std::cout << "Invalid input";
            std::this_thread::sleep_for(1s);
            move_cursor_to(gitBashLineOffset, 22);
            std::cout << "             ";
            move_cursor_to(gitBashLineOffset, 22);
        }
        return input_t(false);
    }
};

#endif //TICTACTOE_CONSOLEREADER_H
