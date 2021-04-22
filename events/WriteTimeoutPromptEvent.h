#ifndef TICTACTOE_WRITETIMEOUTPROMPTEVENT_H
#define TICTACTOE_WRITETIMEOUTPROMPTEVENT_H

#include "GameEvent.h"

class WriteTimeoutPromptEvent : public GameEvent {
    const Player& player;

public:
    explicit WriteTimeoutPromptEvent(const Player &player) : player(player) {}

    const Player &get_player() const {
        return player;
    }

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_TIMEOUT_PROMPT;
    }
};

#endif //TICTACTOE_WRITETIMEOUTPROMPTEVENT_H
