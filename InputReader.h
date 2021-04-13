#ifndef TICTACTOE_INPUTREADER_H
#define TICTACTOE_INPUTREADER_H

#include "Direction.h"

struct input_t {
    MoveDirection move_direction;
    bool set_symbol;

    explicit input_t(MoveDirection move_dir) : move_direction(move_dir), set_symbol(false) {}

    explicit input_t(bool set_symbol) : move_direction(MoveDirection::INVALID), set_symbol(set_symbol) {}
};

class InputReader {
public:
    virtual ~InputReader() = default;

    virtual input_t read() const = 0;
};

#endif //TICTACTOE_INPUTREADER_H
