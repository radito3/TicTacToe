#ifndef TICTACTOE_GAMEENDCONDITIONCHECKER_H
#define TICTACTOE_GAMEENDCONDITIONCHECKER_H

#include <vector>
#include <algorithm>
#include "Worker.h"
#include "../MatrixCell.h"
#include "../events/SwitchPlayerEvent.h"
#include "../events/WriteStrokeEvent.h"
#include "../events/CheckEndConditionEvent.h"
#include "../events/WriteVictoryMessageEvent.h"
#include "../events/WriteDrawMessageEvent.h"

class GameEndConditionChecker : public Worker {
    std::vector<MatrixCell>* game_board;

    static MatrixCell::State get_state(const Player& player) {
        return player.get_symbol() == Symbol::CIRCLE ? MatrixCell::State::CIRCLE : MatrixCell::State::CROSS;
    }

    WriteStrokeEvent* check_for_player_victory(const Player& player) const {
        auto player_state = get_state(player);
        //rows
        for (int row = 0; row < 3; ++row) {
            if (game_board->at(row * 3).state == player_state &&
                    game_board->at((row * 3) + 1).state == player_state &&
                    game_board->at((row * 3) + 2).state == player_state) {
                return new WriteStrokeEvent({0, row}, StrokeDirection::ACROSS);
            }
        }

        //columns
        for (int col = 0; col < 3; ++col) {
            if (game_board->at(col).state == player_state &&
                game_board->at(col + 3).state == player_state &&
                game_board->at(col + 6).state == player_state) {
                return new WriteStrokeEvent({col, 0}, StrokeDirection::DOWN);
            }
        }

        //right diagonal
        if (game_board->at(0).state == player_state &&
            game_board->at(4).state == player_state &&
            game_board->at(8).state == player_state) {
            return new WriteStrokeEvent({0, 0}, StrokeDirection::DIAGONAL_RIGHT);
        }

        //left diagonal
        if (game_board->at(2).state == player_state &&
            game_board->at(4).state == player_state &&
            game_board->at(6).state == player_state) {
            return new WriteStrokeEvent({2, 0}, StrokeDirection::DIAGONAL_LEFT);
        }

        return nullptr;
    }

    bool is_draw() const {
        return std::none_of(game_board->begin(), game_board->end(), [](auto& cell) {
            return cell.state == MatrixCell::State::EMPTY;
        });
    }

public:
    GameEndConditionChecker(GameEventQueue* eventQueue, std::vector<MatrixCell>* gameBoard)
            : Worker(eventQueue), game_board(gameBoard) {}

    void handle_event(GameEvent *event) override {
        auto* ev = dynamic_cast<CheckEndConditionEvent*>(event);
        auto current_player = ev->get_current_player();

        auto write_stroke_event = check_for_player_victory(current_player);
        if (write_stroke_event != nullptr) {
            event_queue->submit_event(write_stroke_event);
            event_queue->submit_event(new WriteVictoryMessageEvent(current_player.get_id()));
            return;
        }

        if (is_draw()) {
            event_queue->submit_event(new WriteDrawMessageEvent);
            return;
        }
        event_queue->submit_event(new SwitchPlayerEvent);
    }

    std::unordered_set<GameEventType> get_supported_event_types() const override {
        return { GameEventType::CHECK_FOR_END_CONDITION };
    }

};

#endif //TICTACTOE_GAMEENDCONDITIONCHECKER_H
