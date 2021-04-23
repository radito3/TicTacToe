#ifndef TICTACTOE_WRITEPLAYERPLACEHOLDERHANDLER_H
#define TICTACTOE_WRITEPLAYERPLACEHOLDERHANDLER_H

#include <vector>
#include "DisplayEventHandler.h"
#include "../MatrixCell.h"
#include "../GameEventQueue.h"
#include "../events/WritePlayerPlaceholderEvent.h"
#include "../events/WaitPlayerInputEvent.h"

class WritePlayerPlaceholderHandler : public DisplayEventHandler {
    std::vector<MatrixCell>* game_board;
    GameEventQueue* event_queue;

    static MatrixCell::State get_placeholder(const Player& player) {
        return player.get_symbol() == Symbol::CIRCLE ? MatrixCell::State::CIRCLE_PLACEHOLDER : MatrixCell::State::CROSS_PLACEHOLDER;
    }

public:
    WritePlayerPlaceholderHandler(std::vector<MatrixCell> *gameBoard, GameEventQueue *eventQueue)
            : game_board(gameBoard), event_queue(eventQueue) {}

    void handle_event(GameEvent *event) override {
        auto *write_ev = dynamic_cast<WritePlayerPlaceholderEvent*>(event);
        auto player = write_ev->get_player();
        auto coord = write_ev->get_coordinate();

        game_board->at(coord.y * 3 + coord.x).state = get_placeholder(player);
        player.write_output([&](auto* writer, auto& p_id, auto p_symbol) {
            writer->write_placeholder_for(p_symbol, coord);
        });

        event_queue->submit_event(new WaitPlayerInputEvent);
    }
};

#endif //TICTACTOE_WRITEPLAYERPLACEHOLDERHANDLER_H
