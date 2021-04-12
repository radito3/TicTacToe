#ifndef TICTACTOE_CONSOLEREADER_H
#define TICTACTOE_CONSOLEREADER_H

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdio>
#include "InputReader.h"
#include "AsciiEscapeCodes.h"

class ConsoleReader : public InputReader {

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
        input_t result{.move_direction = MoveDirection::INVALID};
        move_cursor_to(gitBashLineOffset, 22);
        char ch;
        while (std::cin >> ch) {
            move_cursor_to(gitBashLineOffset, 22);
            if (ch == 'q') {
                result.set_symbol = true;
                break;
            }
            MoveDirection move_dir = parse_move_direction(ch);
            if (move_dir != MoveDirection::INVALID) {
                result.move_direction = move_dir;
                break;
            }
            std::cout << "Invalid input";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            move_cursor_to(gitBashLineOffset, 22);
            std::cout << "             ";
        }
        return result;
    }
};

#endif //TICTACTOE_CONSOLEREADER_H
