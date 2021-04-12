#ifndef TICTACTOE_WAITPLAYERINPUTEVENT_H
#define TICTACTOE_WAITPLAYERINPUTEVENT_H

#include "GameEvent.h"

class WaitPlayerInputEvent : public GameEvent {
public:

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WAIT_PLAYER_INPUT;
    }
};

#endif //TICTACTOE_WAITPLAYERINPUTEVENT_H
