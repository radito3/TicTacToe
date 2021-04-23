#ifndef TICTACTOE_DISPLAYEVENTHANDLER_H
#define TICTACTOE_DISPLAYEVENTHANDLER_H

#include "../events/GameEvent.h"

class DisplayEventHandler {
public:
    virtual ~DisplayEventHandler() = default;

    virtual void handle_event(GameEvent* event) = 0;
};

#endif //TICTACTOE_DISPLAYEVENTHANDLER_H
