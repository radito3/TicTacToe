#ifndef TICTACTOE_WRITEVICTORYMESSAGEEVENT_H
#define TICTACTOE_WRITEVICTORYMESSAGEEVENT_H

#include <string>
#include <utility>
#include "GameEvent.h"

class WriteVictoryMessageEvent : public GameEvent {
    std::string player_id;

public:
    explicit WriteVictoryMessageEvent(std::string playerId) : player_id(std::move(playerId)) {}

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_VICTORY_MSG;
    }

    const std::string &get_player_id() const {
        return player_id;
    }
};


#endif //TICTACTOE_WRITEVICTORYMESSAGEEVENT_H
