#ifndef TICTACTOE_WRITEDEADLOCKMESSAGEEVENT_H
#define TICTACTOE_WRITEDEADLOCKMESSAGEEVENT_H

#include "GameEvent.h"

class WriteDeadlockMessageEvent : public GameEvent {
public:

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_DEADLOCK_MSG;
    }
};

#endif //TICTACTOE_WRITEDEADLOCKMESSAGEEVENT_H
