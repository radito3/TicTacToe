#ifndef TICTACTOE_WRITEDRAWMESSAGEEVENT_H
#define TICTACTOE_WRITEDRAWMESSAGEEVENT_H

#include "GameEvent.h"

class WriteDrawMessageEvent : public GameEvent {
public:

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_DRAW_MSG;
    }
};

#endif //TICTACTOE_WRITEDRAWMESSAGEEVENT_H
