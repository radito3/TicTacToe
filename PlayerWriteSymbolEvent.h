#ifndef TICTACTOE_PLAYERWRITESYMBOLEVENT_H
#define TICTACTOE_PLAYERWRITESYMBOLEVENT_H

#include "GameEvent.h"

class PlayerWriteSymbolEvent : public GameEvent {

public:


    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_PLAYER_SYMBOL;
    }
};

#endif //TICTACTOE_PLAYERWRITESYMBOLEVENT_H
