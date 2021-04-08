#ifndef TICTACTOE_MATRIXCELL_H
#define TICTACTOE_MATRIXCELL_H

struct MatrixCell {
    enum class State {
        EMPTY, PLAYER_1_SYMBOL, PLAYER_2_SYMBOL, PLAYER_1_PLACEHOLDER, PLAYER_2_PLACEHOLDER
    };

    State state;
    bool is_current;

    explicit MatrixCell(State state, bool is_current = false) : state(state), is_current(is_current) {}

};

#endif //TICTACTOE_MATRIXCELL_H
