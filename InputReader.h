#ifndef TICTACTOE_INPUTREADER_H
#define TICTACTOE_INPUTREADER_H

#include "Direction.h"

union input_t {
    MoveDirection move_direction;
    bool set_symbol;
};

class InputReader {
public:
    virtual ~InputReader() = default;

    virtual input_t read() const = 0;
};

#endif //TICTACTOE_INPUTREADER_H
