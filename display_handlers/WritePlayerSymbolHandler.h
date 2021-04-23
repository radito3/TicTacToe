#ifndef TICTACTOE_WRITEPLAYERSYMBOLHANDLER_H
#define TICTACTOE_WRITEPLAYERSYMBOLHANDLER_H

#include <vector>
#include "DisplayEventHandler.h"
#include "../GameEventQueue.h"
#include "../MatrixCell.h"
#include "../events/WritePlayerSymbolEvent.h"
#include "../events/CheckEndConditionEvent.h"

class WritePlayerSymbolHandler : public DisplayEventHandler {
    std::vector<MatrixCell>* game_board;
    GameEventQueue* event_queue;
    const Player& player1;
    const Player& player2;

    static MatrixCell::State get_state(const Player& player) {
        return player.get_symbol() == Symbol::CIRCLE ? MatrixCell::State::CIRCLE : MatrixCell::State::CROSS;
    }

    static MatrixCell::State get_placeholder(const Player& player) {
        return player.get_symbol() == Symbol::CIRCLE ? MatrixCell::State::CIRCLE_PLACEHOLDER : MatrixCell::State::CROSS_PLACEHOLDER;
    }

    template<typename Function>
    void write_to_both_players(Function&& function) {
        player1.write_output(std::forward<Function>(function));
        player2.write_output(std::forward<Function>(function));
    }

    void clear_active_cells() {
        for (auto& cell : *game_board) {
            cell.is_current = false;
        }
    }

    int get_next_available_pos() const {
        for (int i = 0; i < game_board->size(); ++i) {
            if (game_board->at(i).state == MatrixCell::State::EMPTY) {
                return i;
            }
        }
        return -1;
    }

public:
    WritePlayerSymbolHandler(std::vector<MatrixCell> *gameBoard, GameEventQueue *eventQueue,
                             const Player &player1, const Player &player2)
             : game_board(gameBoard), event_queue(eventQueue), player1(player1), player2(player2) {}

    void handle_event(GameEvent *event) override {
        auto* write_symbol_ev = dynamic_cast<WritePlayerSymbolEvent*>(event);
        auto player = write_symbol_ev->get_current_player();
        auto coord = write_symbol_ev->get_current_coord();
        int matrix_index = coord.y * 3 + coord.x;

        if (game_board->at(matrix_index).state != get_placeholder(player)) {
            throw std::runtime_error("current coordinate doesn't match current player's placeholder");
        }
        game_board->at(matrix_index).state = get_state(player);
        write_to_both_players([&](auto* writer, auto& p_id, auto p_symbol) {
            writer->clear_cell_at(coord);
            writer->write_symbol(player.get_symbol(), coord);
        });

        clear_active_cells();
        int next_avail_pos = get_next_available_pos();
        if (next_avail_pos != -1) {
            game_board->at(next_avail_pos).is_current = true;
        }
        event_queue->submit_event(new CheckEndConditionEvent(player));
    }
};

#endif //TICTACTOE_WRITEPLAYERSYMBOLHANDLER_H
