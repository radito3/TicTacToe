#ifndef TICTACTOE_GAMESWITCHPLAYEREVENT_H
#define TICTACTOE_GAMESWITCHPLAYEREVENT_H

#include "GameEvent.h"

class GameSwitchPlayerEvent : public GameEvent {
public:

    GameEventType get_event_type() const noexcept override {
        return GameEventType::SWITCH_PLAYER;
    }
};

#endif //TICTACTOE_GAMESWITCHPLAYEREVENT_H
