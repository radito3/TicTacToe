#ifndef TICTACTOE_SHUTDOWNEVENT_H
#define TICTACTOE_SHUTDOWNEVENT_H

#include "GameEvent.h"

class ShutdownEvent : public GameEvent {
public:

    GameEventType get_event_type() const noexcept override {
        return GameEventType::SHUTDOWN;
    }
};

#endif //TICTACTOE_SHUTDOWNEVENT_H
