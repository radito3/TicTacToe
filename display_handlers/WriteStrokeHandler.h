#ifndef TICTACTOE_WRITESTROKEHANDLER_H
#define TICTACTOE_WRITESTROKEHANDLER_H

#include "DisplayEventHandler.h"
#include "../Player.h"
#include "../events/WriteStrokeEvent.h"

class WriteStrokeHandler : public DisplayEventHandler {
    const Player& player1;
    const Player& player2;

public:
    WriteStrokeHandler(const Player &player1, const Player &player2) : player1(player1), player2(player2) {}

    void handle_event(GameEvent *event) override {
        auto *write_ev = dynamic_cast<WriteStrokeEvent*>(event);

        player1.write_output([&](auto* writer, auto& p_id, auto p_symbol) {
            writer->write_stroke(write_ev->get_coord(), write_ev->get_direction());
        });
        player2.write_output([&](auto* writer, auto& p_id, auto p_symbol) {
            writer->write_stroke(write_ev->get_coord(), write_ev->get_direction());
        });
    }
};

#endif //TICTACTOE_WRITESTROKEHANDLER_H
