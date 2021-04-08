#ifndef TICTACTOE_CONSOLEWRITER_H
#define TICTACTOE_CONSOLEWRITER_H

#include <iostream>
#include <cstring>
#include "DisplayWriter.h"
#include "AsciiEscapeCodes.h"

class ConsoleWriter : public DisplayWriter {

    const int gitBashLineOffset = 4;

    const int symbols_per_line = 3;
    const int symbols_per_column = 5;

    static void move_cursor_to(int line, int column) {
        printf(AsciiEscapeCodes::MoveToPos, line, column);
    }

    [[nodiscard]] std::pair<int, int> determine_start_coordinates(const Coordinate& coord) const noexcept {
        int coord_x = coord.x;
        int coord_y = coord.y;
        int start_column = coord_x > 0 ? coord_x * symbols_per_column + 2 : 0;
        int start_line = coord_y > 0 ? coord_y * symbols_per_line + 1 : 0;
        return { start_column, start_line };
    }

public:

/*
 * xx-xx|x\x/x|xxxx/
 * /xxx\|xxXxx|xx//x
 * \x_x/|x/x\x|//xxx
 * - - - - - - - - -
 * \xxxx|\xxxx|xxxxx
 * x\\xx|x\\xx|xxxxx
 * xxx\\|xxx\\|
 * - - - - - - - - -
 * xxxxx|xxxxx|xxxxx
 *
 */

    void write_grid() const override {
        for (int line = 0; line < 11; line++) {
            if (line == 3|| line == 7) {
                std::cout << "- - - - - - - - -" << std::endl;
                continue;
            }
            move_cursor_to(line + gitBashLineOffset, 6);
            std::cout << '|';
            move_cursor_to(line + gitBashLineOffset, 12);
            std::cout << '|' << std::endl;
        }
    }

    void write_cross(const Coordinate &coordinate) const override {
        auto [ start_column, start_line ] = determine_start_coordinates(coordinate);

        move_cursor_to(start_line + gitBashLineOffset, start_column);
        std::cout << " \\ / ";
        move_cursor_to(start_line + gitBashLineOffset + 1, start_column);
        std::cout << "  X  ";
        move_cursor_to(start_line + gitBashLineOffset + 2, start_column);
        std::cout << " / \\ ";
    }

    void write_cross_placeholder(const Coordinate& coordinate) const override {
        auto [ start_column, start_line ] = determine_start_coordinates(coordinate);
        int line_offset = coordinate.y == 0 ? 1 : coordinate.y;
        int column_offset = coordinate.x == 0 ? 3 : coordinate.x + 1;

        move_cursor_to(start_line + gitBashLineOffset + line_offset, start_column + column_offset);
        std::cout << 'x';
    }

    void write_circle(const Coordinate &coordinate) const override {
        auto [ start_column, start_line ] = determine_start_coordinates(coordinate);

        move_cursor_to(start_line + gitBashLineOffset, start_column);
        std::cout << "  _  ";
        move_cursor_to(start_line + gitBashLineOffset + 1, start_column);
        std::cout << "/   \\";
        move_cursor_to(start_line + gitBashLineOffset + 2, start_column);
        std::cout << "\\ _ /";
    }

    void write_circle_placeholder(const Coordinate& coordinate) const override {
        auto [ start_column, start_line ] = determine_start_coordinates(coordinate);
        int line_offset = coordinate.y == 0 ? 1 : coordinate.y;
        int column_offset = coordinate.x == 0 ? 3 : coordinate.x + 1;

        move_cursor_to(start_line + gitBashLineOffset + line_offset, start_column + column_offset);
        std::cout << 'o';
    }

    void write_stroke(const Coordinate &coordinate, StrokeDirection direction) const override {
        auto [ start_column, start_line ] = determine_start_coordinates(coordinate);

        switch (direction) {
            case StrokeDirection::DOWN:
                for (int line_offset = 0; line_offset < 11; line_offset++) {
                    if (line_offset == 3 || line_offset == 7) {
                        continue;
                    }
                    move_cursor_to(start_line + gitBashLineOffset + line_offset, start_column + 2);
                    std::cout << '|';
                }
                break;
            case StrokeDirection::ACROSS:
                move_cursor_to(start_line + gitBashLineOffset + 1, start_column);
                std::cout << "-----";
                move_cursor_to(start_line + gitBashLineOffset + 1, start_column + 7);
                std::cout << "-----";
                move_cursor_to(start_line + gitBashLineOffset + 1, start_column + 13);
                std::cout << "-----";
                break;
            case StrokeDirection::DIAGONAL_RIGHT:
                move_cursor_to(start_line + gitBashLineOffset, start_column);
                std::cout << '\\';
                move_cursor_to(start_line + gitBashLineOffset + 1, start_column + 2);
                std::cout << "\\\\";
                move_cursor_to(start_line + gitBashLineOffset + 2, start_column + 4);
                std::cout << "\\\\";

                move_cursor_to(start_line + gitBashLineOffset + 4, start_column + 7);
                std::cout << '\\';
                move_cursor_to(start_line + gitBashLineOffset + 5, start_column + 8);
                std::cout << "\\\\";
                move_cursor_to(start_line + gitBashLineOffset + 6, start_column + 10);
                std::cout << "\\\\";

                move_cursor_to(start_line + gitBashLineOffset + 8, start_column + 13);
                std::cout << '\\';
                move_cursor_to(start_line + gitBashLineOffset + 9, start_column + 14);
                std::cout << "\\\\";
                move_cursor_to(start_line + gitBashLineOffset + 10, start_column + 16);
                std::cout << "\\\\";
                break;
            case StrokeDirection::DIAGONAL_LEFT:
                move_cursor_to(start_line + gitBashLineOffset, start_column + 5);
                std::cout << '/';
                move_cursor_to(start_line + gitBashLineOffset + 1, start_column + 3);
                std::cout << "//";
                move_cursor_to(start_line + gitBashLineOffset + 2, start_column + 1);
                std::cout << "//";

                move_cursor_to(start_line + gitBashLineOffset + 4, start_column - 1);
                std::cout << '/';
                move_cursor_to(start_line + gitBashLineOffset + 5, start_column - 3);
                std::cout << "//";
                move_cursor_to(start_line + gitBashLineOffset + 6, start_column - 5);
                std::cout << "//";

                move_cursor_to(start_line + gitBashLineOffset + 8, start_column - 7);
                std::cout << '/';
                move_cursor_to(start_line + gitBashLineOffset + 9, start_column - 9);
                std::cout << "//";
                move_cursor_to(start_line + gitBashLineOffset + 10, start_column - 10);
                std::cout << "//";
                break;
        }

    }
};

#endif //TICTACTOE_CONSOLEWRITER_H
