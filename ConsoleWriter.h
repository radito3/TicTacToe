#ifndef TICTACTOE_CONSOLEWRITER_H
#define TICTACTOE_CONSOLEWRITER_H

#include <iostream>
#include <cstring>
#include "DisplayWriter.h"

class ConsoleWriter : public DisplayWriter {

    struct AsciiEscapeCodes {
        constexpr static const char * Up = "\u001b[%dA";
        constexpr static const char * Down = "\u001b[%dB";
        constexpr static const char * Right = "\u001b[%dC";
        constexpr static const char * Left = "\u001b[%dD";
        constexpr static const char * MoveToPos = "\x1b[%d;%dH";
    };

    const int gitBashLineOffset = 4;

    const int symbols_per_line = 3;
    const int symbols_per_column = 5;

    static void move_cursor_to(int line, int column) {
        char* buff = new char[strlen(AsciiEscapeCodes::MoveToPos) + 5];
        sprintf(buff, AsciiEscapeCodes::MoveToPos, line, column);
        std::cout << buff;
        delete [] buff;
    }

    [[nodiscard]] std::pair<int, int> determine_start_coordinates(const Coordinate& coord) const noexcept {
        int coord_x = coord.x;
        int coord_y = coord.y;
        int start_x = coord_x > 0 ? coord_x * symbols_per_column + 2 : 0;
        int start_y = coord_y > 0 ? coord_y * symbols_per_line + 1 : 0;
        return { start_x, start_y };
    }

public:

/*
 * xx-xx|x\x/x|xxxxx
 * /xxx\|xxXxx|xxxxx
 * \x_x/|x/x\x|xxxxx
 * - - - - - - - - -
 * \xxxx|\xxxx|xxxxx
 * x\\xx|x\\xx|xxxxx
 * xxx\\|xxx\\|
 * - - - - - - - - -
 * xxxxx|xxxxx|xxxxx
 *
 */

    void write_grid() const override {
        for (int i = 0 + gitBashLineOffset; i < 11 + gitBashLineOffset; i++) {
            if (i == 3 + gitBashLineOffset || i == 7 + gitBashLineOffset) {
                std::cout << "- - - - - - - - -" << std::endl;
                continue;
            }
            move_cursor_to(i, 6);
            std::cout << '|';
            move_cursor_to(i, 12);
            std::cout << '|' << std::endl;
        }
    }

    void write_cross(const Coordinate &coordinate) const override {
        auto [ start_x, start_y ] = determine_start_coordinates(coordinate);

        move_cursor_to(start_y + gitBashLineOffset, start_x);
        std::cout << " \\ / ";
        move_cursor_to(start_y + gitBashLineOffset + 1, start_x);
        std::cout << "  X  ";
        move_cursor_to(start_y + gitBashLineOffset + 2, start_x);
        std::cout << " / \\ ";
    }

    void write_circle(const Coordinate &coordinate) const override {
        auto [ start_x, start_y ] = determine_start_coordinates(coordinate);

        move_cursor_to(start_y + gitBashLineOffset, start_x);
        std::cout << "  _  ";
        move_cursor_to(start_y + gitBashLineOffset + 1, start_x);
        std::cout << "/   \\";
        move_cursor_to(start_y + gitBashLineOffset + 2, start_x);
        std::cout << "\\ _ /";
    }

    void write_stroke(const Coordinate &coordinate, Direction direction) const override {
        auto [ start_x, start_y ] = determine_start_coordinates(coordinate);

        if (direction == DIAGONAL) {
            throw std::runtime_error("not yet implemented");
        }

        move_cursor_to(start_y + gitBashLineOffset, start_x);

        if (direction == DOWN) {
            //needs debuging...
            std::cout << "  |  ";
            move_cursor_to(start_y + gitBashLineOffset + 1, start_x);
            std::cout << "  |  ";
            move_cursor_to(start_y + gitBashLineOffset + 2, start_x);
            std::cout << "  |  ";
        } else if (direction == ACROSS) {
            //...
        }
    }
};

#endif //TICTACTOE_CONSOLEWRITER_H
