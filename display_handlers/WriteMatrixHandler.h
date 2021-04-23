#ifndef TICTACTOE_WRITEMATRIXHANDLER_H
#define TICTACTOE_WRITEMATRIXHANDLER_H

#include "DisplayEventHandler.h"
#include "../Player.h"

class WriteMatrixHandler : public DisplayEventHandler {
    const Player& player1;
    const Player& player2;

public:
    WriteMatrixHandler(const Player &player1, const Player &player2) : player1(player1), player2(player2) {}

    void handle_event(GameEvent *event) override {
        player1.write_output([](auto* writer, auto& p_id, auto p_symbol) {
            writer->write_grid();
        });
        player2.write_output([](auto* writer, auto& p_id, auto p_symbol) {
            writer->write_grid();
        });
    }
};

#endif //TICTACTOE_WRITEMATRIXHANDLER_H
