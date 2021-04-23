#ifndef TICTACTOE_WRITEVICTORYMESSAGEHANDLER_H
#define TICTACTOE_WRITEVICTORYMESSAGEHANDLER_H

#include <sstream>
#include "DisplayEventHandler.h"
#include "../GameEventQueue.h"
#include "../Player.h"
#include "../events/WriteVictoryMessageEvent.h"
#include "../events/ShutdownEvent.h"

class WriteVictoryMessageHandler : public DisplayEventHandler {
    GameEventQueue* event_queue;
    const Player& player1;
    const Player& player2;

    const Player& get_victor(const std::string& winner_id) const {
        return winner_id == player1.get_id() ? player1 : player2;
    }

    const Player& get_loser(const std::string& winner_id) const {
        return winner_id == player1.get_id() ? player2 : player1;
    }

public:
    WriteVictoryMessageHandler(GameEventQueue *eventQueue, const Player &player1, const Player &player2)
            : event_queue(eventQueue), player1(player1), player2(player2) {}

    void handle_event(GameEvent *event) override {
        auto *write_ev = dynamic_cast<WriteVictoryMessageEvent*>(event);
        auto winner_id = write_ev->get_player_id();

        get_victor(winner_id).write_output([](auto* writer, auto& p_id, auto p_symbol) {
            writer->write_msg("You are victorious");
        });
        get_loser(winner_id).write_output([&](auto* writer, auto& p_id, auto p_symbol) {
            std::stringstream ss;
            ss << winner_id << " is victorious";
            writer->write_msg(ss.str().data());
        });

        event_queue->submit_event(new ShutdownEvent);
    }
};

#endif //TICTACTOE_WRITEVICTORYMESSAGEHANDLER_H
