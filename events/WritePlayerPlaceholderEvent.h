#ifndef TICTACTOE_WRITEPLAYERPLACEHOLDEREVENT_H
#define TICTACTOE_WRITEPLAYERPLACEHOLDEREVENT_H

#include "GameEvent.h"

class WritePlayerPlaceholderEvent : public GameEvent {
    const Player& player;
    const Coordinate& coordinate;

public:
    WritePlayerPlaceholderEvent(const Player &player, const Coordinate &coordinate)
            : player(player), coordinate(coordinate) {}

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_PLAYER_PLACEHOLDER;
    }

    const Player &get_player() const {
        return player;
    }

    const Coordinate &get_coordinate() const {
        return coordinate;
    }
};

#endif //TICTACTOE_WRITEPLAYERPLACEHOLDEREVENT_H
