#ifndef TICTACTOE_SWITCHPLAYEREVENT_H
#define TICTACTOE_SWITCHPLAYEREVENT_H

#include "GameEvent.h"

class SwitchPlayerEvent : public GameEvent {
public:

    GameEventType get_event_type() const noexcept override {
        return GameEventType::SWITCH_PLAYER;
    }
};

#endif //TICTACTOE_SWITCHPLAYEREVENT_H
