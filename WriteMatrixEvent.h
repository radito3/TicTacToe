#ifndef TICTACTOE_WRITEMATRIXEVENT_H
#define TICTACTOE_WRITEMATRIXEVENT_H

#include "GameEvent.h"

class WriteMatrixEvent : public GameEvent {

public:

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_MATRIX;
    }
};

#endif //TICTACTOE_WRITEMATRIXEVENT_H
