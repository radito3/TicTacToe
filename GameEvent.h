#ifndef TICTACTOE_GAMEEVENT_H
#define TICTACTOE_GAMEEVENT_H

#include <tuple>
#include "GameEventType.h"

class GameEvent {
public:
    virtual ~GameEvent() = default;

    virtual GameEventType get_event_type() const noexcept = 0;

};

#endif //TICTACTOE_GAMEEVENT_H
