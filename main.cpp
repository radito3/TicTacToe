#include <iostream>
#include "ConsoleWriter.h"

int main() {
    ConsoleWriter writer;
    writer.write_grid();
    writer.write_cross({0, 0});
    writer.write_circle({1, 1});
//    writer.write_stroke({2, 0}, DOWN);
    char* buff = new char[strlen("\x1b[%d;%dH") + 5];
    sprintf(buff, "\x1b[%d;%dH", 15, 15);
    std::cout << buff;
    delete [] buff;
    return 0;
}
