#ifndef TICTACTOE_GAMEEVENTTYPE_H
#define TICTACTOE_GAMEEVENTTYPE_H

enum class GameEventType {
    WRITE_MATRIX, WRITE_PLAYER_PLACEHOLDER, MOVE_PLAYER_PLACEHOLDER, WRITE_PLAYER_SYMBOL, WAIT_PLAYER_INPUT,
    SWITCH_PLAYER, CHECK_FOR_END_CONDITION, WRITE_TIMEOUT_PROMPT, WRITE_STROKE, WRITE_VICTORY_MSG, WRITE_DRAW_MSG,
    SHUTDOWN
};

#endif //TICTACTOE_GAMEEVENTTYPE_H
