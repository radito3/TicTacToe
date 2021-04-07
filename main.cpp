#include <iostream>
#include "ConsoleWriter.h"

int main() {
    ConsoleWriter writer;
    writer.write_grid();
//    writer.write_cross({0, 0});
//    writer.write_circle({1, 1});
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
//            writer.write_circle_placeholder({i, j});
            writer.write_cross_placeholder({i, j});
        }
    }
//    writer.write_stroke({0, 0}, DIAGONAL_RIGHT);
//    writer.write_stroke({2, 0}, DIAGONAL_LEFT);


    printf(AsciiEscapeCodes::MoveToPos, 15, 15);
    return 0;
}
