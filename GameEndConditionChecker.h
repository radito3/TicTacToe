#ifndef TICTACTOE_GAMEENDCONDITIONCHECKER_H
#define TICTACTOE_GAMEENDCONDITIONCHECKER_H

#include <vector>
#include "Worker.h"
#include "MatrixCell.h"
#include "events/GameSwitchPlayerEvent.h"
#include "events/GameCheckEndConditionEvent.h"

class GameEndConditionChecker : public Worker {
    std::vector<MatrixCell>& game_board;

public:
    GameEndConditionChecker(GameEventQueue &eventQueue, std::vector<MatrixCell> &gameBoard)
            : Worker(eventQueue), game_board(gameBoard) {}

    void handle_event(GameEvent *event) override {
        auto* ev = dynamic_cast<GameCheckEndConditionEvent*>(event);
        auto& current_player = ev->get_current_player();
        //check for victory
        //check for deadlock
        event_queue.submit_event(new GameSwitchPlayerEvent);
    }

    std::unordered_set<GameEventType> get_supported_event_types() const override {
        return { GameEventType::CHECK_FOR_END_CONDITION };
    }

};

#endif //TICTACTOE_GAMEENDCONDITIONCHECKER_H
