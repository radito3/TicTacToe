#ifndef TICTACTOE_CHECKENDCONDITIONEVENT_H
#define TICTACTOE_CHECKENDCONDITIONEVENT_H

#include "GameEvent.h"
#include "../Player.h"

class CheckEndConditionEvent : public GameEvent {
    const Player& current_player;

public:
    explicit CheckEndConditionEvent(const Player &currentPlayer) : current_player(currentPlayer) {}

    GameEventType get_event_type() const noexcept override {
        return GameEventType::CHECK_FOR_END_CONDITION;
    }

    const Player &get_current_player() const {
        return current_player;
    }
};

#endif //TICTACTOE_CHECKENDCONDITIONEVENT_H
