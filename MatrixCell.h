#ifndef TICTACTOE_MATRIXCELL_H
#define TICTACTOE_MATRIXCELL_H

struct MatrixCell {
    enum class State {
        EMPTY, CROSS, CIRCLE, CROSS_PLACEHOLDER, CIRCLE_PLACEHOLDER
    };

    State state;
    bool is_current;

    explicit MatrixCell(State state = State::EMPTY, bool is_current = false)
            : state(state), is_current(is_current) {}

};

#endif //TICTACTOE_MATRIXCELL_H
