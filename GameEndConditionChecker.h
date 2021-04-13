#ifndef TICTACTOE_GAMEENDCONDITIONCHECKER_H
#define TICTACTOE_GAMEENDCONDITIONCHECKER_H

#include <vector>
#include <valarray>
#include "Worker.h"
#include "MatrixCell.h"
#include "events/SwitchPlayerEvent.h"
#include "events/WriteStrokeEvent.h"
#include "events/CheckEndConditionEvent.h"
#include "events/WriteVictoryMessageEvent.h"
#include "events/WriteDeadlockMessageEvent.h"

class GameEndConditionChecker : public Worker {
    std::vector<MatrixCell>& game_board;

    static MatrixCell::State get_state(const Player& player) {
        return player.get_symbol() == Symbol::CIRCLE ? MatrixCell::State::CIRCLE : MatrixCell::State::CROSS;
    }

    WriteStrokeEvent* check_for_player_victory(const Player& player) const {
        auto player_state = get_state(player);
        //rows
        for (int row = 0; row < 3; ++row) {
            if (game_board[row * 3].state == player_state &&
                    game_board[(row * 3) + 1].state == player_state &&
                    game_board[(row * 3) + 2].state == player_state) {
                return new WriteStrokeEvent({0, row}, StrokeDirection::ACROSS);
            }
        }

        //columns
        for (int col = 0; col < 3; ++col) {
            if (game_board[col].state == player_state &&
                game_board[col + 3].state == player_state &&
                game_board[col + 6].state == player_state) {
                return new WriteStrokeEvent({col, 0}, StrokeDirection::DOWN);
            }
        }

        //right diagonal
        if (game_board[0].state == player_state &&
            game_board[4].state == player_state &&
            game_board[8].state == player_state) {
            return new WriteStrokeEvent({0, 0}, StrokeDirection::DIAGONAL_RIGHT);
        }

        //left diagonal
        if (game_board[2].state == player_state &&
            game_board[4].state == player_state &&
            game_board[6].state == player_state) {
            return new WriteStrokeEvent({2, 0}, StrokeDirection::DIAGONAL_LEFT);
        }

        return nullptr;
    }

    bool is_different_pair(int index, int increment) const {
        if (game_board[index].state == MatrixCell::State::EMPTY ||
            game_board[index + increment].state == MatrixCell::State::EMPTY) {
            return false;
        }
        return game_board[index].state != game_board[index + increment].state;
    }

    //see https://en.cppreference.com/w/cpp/language/fold for details
    template<typename... Args>
    bool all(Args... args) const {
        return (... && args);
    }

    bool is_deadlock() const {
        bool rows, cols, right_diag, left_diag;
        //rows
        for (int row = 0; row < 3; ++row) {
            if (is_different_pair(row * 3, 1) ||
                    is_different_pair((row * 3) + 1, 1)) {
                rows = true;
            }
        }

        //columns
        for (int col = 0; col < 3; ++col) {
            if (is_different_pair(col, 3) ||
                    is_different_pair(col + 3, 3)) {
                cols = true;
            }
        }

        //right diagonal
        if (is_different_pair(0, 4) ||
                is_different_pair(4, 4)) {
            right_diag = true;
        }

        //left diagonal
        if (is_different_pair(2, 2) ||
                is_different_pair(4, 2)) {
            left_diag = true;
        }

        return all(rows, cols, right_diag, left_diag);
    }

public:
    GameEndConditionChecker(GameEventQueue &eventQueue, std::vector<MatrixCell> &gameBoard)
            : Worker(eventQueue), game_board(gameBoard) {}

    void handle_event(GameEvent *event) override {
        auto* ev = dynamic_cast<CheckEndConditionEvent*>(event);
        auto current_player = ev->get_current_player();

        auto write_stroke_event = check_for_player_victory(current_player);
        if (write_stroke_event != nullptr) {
            event_queue.submit_event(write_stroke_event);
            event_queue.submit_event(new WriteVictoryMessageEvent(current_player.get_id()));
            return;
        }

        if (is_deadlock()) {
            event_queue.submit_event(new WriteDeadlockMessageEvent);
            return;
        }
        event_queue.submit_event(new SwitchPlayerEvent);
    }

    std::unordered_set<GameEventType> get_supported_event_types() const override {
        return { GameEventType::CHECK_FOR_END_CONDITION };
    }

};

#endif //TICTACTOE_GAMEENDCONDITIONCHECKER_H
