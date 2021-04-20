#ifndef TICTACTOE_ASCIIESCAPECODES_H
#define TICTACTOE_ASCIIESCAPECODES_H

namespace AsciiEscapeCodes {
    static const char * Up = "\x1b[%dA";
    static const char * Down = "\x1b[%dB";
    static const char * Right = "\x1b[%dC";
    static const char * Left = "\x1b[%dD";
    static const char * MoveToPos = "\x1b[%d;%dH";
    static const char * RedTextColor = "\x1b[31m";
    static const char * ResetTextColor = "\x1b[0m";
}

#endif //TICTACTOE_ASCIIESCAPECODES_H
