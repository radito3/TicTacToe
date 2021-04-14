#ifndef TICTACTOE_CONSOLEWRITER_H
#define TICTACTOE_CONSOLEWRITER_H

#include <iostream>
#include <array>
#include "DisplayWriter.h"
#include "AsciiEscapeCodes.h"
#include "Symbol.h"

class ConsoleWriter : public DisplayWriter {

    const int gitBashLineOffset = 4;

    const int symbols_per_line = 3;
    const int symbols_per_column = 5;

    static void move_cursor_to(int line, int column) {
        printf(AsciiEscapeCodes::MoveToPos, line, column);
    }

    static std::array<const char*, 3> get_circle_elements() {
        return {"  _  ",
                "/   \\",
                "\\ _ /"};
    }

    static std::array<const char*, 3> get_cross_elements() {
        return {" \\ / ",
                "  X  ",
                " / \\ "};
    }

    std::pair<int, int> determine_start_coordinates(const Coordinate& coord) const noexcept {
        int coord_x = coord.x;
        int coord_y = coord.y;
        int start_column = coord_x > 0 ? (coord_x * symbols_per_column) + coord_x + 1 : 0;
        int start_line = coord_y > 0 ? (coord_y * symbols_per_line) + coord_y : 0;
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

    void clear_cell_at(const Coordinate& coordinate) const override {
        auto [ start_column, start_line ] = determine_start_coordinates(coordinate);
        auto* str = "     ";

        for (int i = 0; i < 3; ++i) {
            move_cursor_to(start_line + gitBashLineOffset + i, start_column);
            std::cout << str;
        }
    }

    void write_symbol(Symbol symbol, const Coordinate& coordinate) const override {
        auto [ start_column, start_line ] = determine_start_coordinates(coordinate);
        std::array<const char*, 3> symbol_elements = symbol == Symbol::CIRCLE ? get_circle_elements() : get_cross_elements();

        for (int i = 0; i < 3; ++i) {
            move_cursor_to(start_line + gitBashLineOffset + i, start_column);
            std::cout << symbol_elements[i];
        }
    }

    void write_placeholder_for(Symbol symbol, const Coordinate& coordinate) const override {
        auto [ start_column, start_line ] = determine_start_coordinates(coordinate);
        int column_offset = coordinate.x == 0 ? 3 : 2;
        auto _symbol = symbol == Symbol::CIRCLE ? 'o' : 'x';

        move_cursor_to(start_line + gitBashLineOffset + 1, start_column + column_offset);
        std::cout << _symbol;
    }

    void write_stroke(const Coordinate &coordinate, StrokeDirection direction) const override {
        auto [ start_column, start_line ] = determine_start_coordinates(coordinate);

        switch (direction) {
            case StrokeDirection::DOWN:
                for (int line_offset = 0; line_offset < 11; line_offset++) {
                    if (line_offset == 3 || line_offset == 7) {
                        continue;
                    }
                    int column_offset = coordinate.x == 0 ? 3 : 2;
                    move_cursor_to(start_line + gitBashLineOffset + line_offset, start_column + column_offset);
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
                move_cursor_to(start_line + gitBashLineOffset, start_column + 4);
                std::cout << '/';
                move_cursor_to(start_line + gitBashLineOffset + 1, start_column + 2);
                std::cout << "//";
                move_cursor_to(start_line + gitBashLineOffset + 2, start_column);
                std::cout << "//";

                move_cursor_to(start_line + gitBashLineOffset + 4, start_column - 2);
                std::cout << '/';
                move_cursor_to(start_line + gitBashLineOffset + 5, start_column - 4);
                std::cout << "//";
                move_cursor_to(start_line + gitBashLineOffset + 6, start_column - 6);
                std::cout << "//";

                move_cursor_to(start_line + gitBashLineOffset + 8, start_column - 8);
                std::cout << '/';
                move_cursor_to(start_line + gitBashLineOffset + 9, start_column - 10);
                std::cout << "//";
                move_cursor_to(start_line + gitBashLineOffset + 10, start_column - 12);
                std::cout << "//";
                break;
        }

    }

    void write_victory_msg_for(const std::string &player_id) const override {
        move_cursor_to(gitBashLineOffset, 22);
        std::cout << "Player \"" << player_id << "\" is victorious";
    }

    void write_draw_msg() const override {
        move_cursor_to(gitBashLineOffset, 22);
        std::cout << "Draw";
    }
};

#endif //TICTACTOE_CONSOLEWRITER_H
