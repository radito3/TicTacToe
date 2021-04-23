#ifndef TICTACTOE_WRITEDRAWMESSAGEHANDLER_H
#define TICTACTOE_WRITEDRAWMESSAGEHANDLER_H

#include "DisplayEventHandler.h"
#include "../GameEventQueue.h"
#include "../Player.h"
#include "../events/WriteVictoryMessageEvent.h"
#include "../events/ShutdownEvent.h"

class WriteDrawMessageHandler : public DisplayEventHandler {
    GameEventQueue* event_queue;
    const Player& player1;
    const Player& player2;

public:
    WriteDrawMessageHandler(GameEventQueue *eventQueue, const Player &player1, const Player &player2)
            : event_queue(eventQueue), player1(player1), player2(player2) {}

    void handle_event(GameEvent *event) override {
        player1.write_output([](auto* writer, auto& p_id, auto p_symbol) {
            writer->write_msg("Draw");
        });
        player2.write_output([](auto* writer, auto& p_id, auto p_symbol) {
            writer->write_msg("Draw");
        });

        event_queue->submit_event(new ShutdownEvent);
    }
};

#endif //TICTACTOE_WRITEDRAWMESSAGEHANDLER_H
