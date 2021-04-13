#ifndef TICTACTOE_WRITEPLAYERPLACEHOLDEREVENT_H
#define TICTACTOE_WRITEPLAYERPLACEHOLDEREVENT_H

#include "GameEvent.h"

class WritePlayerPlaceholderEvent : public GameEvent {
    Player player;
    Coordinate coordinate;

public:
    WritePlayerPlaceholderEvent(Player player, const Coordinate &coordinate)
            : player(player), coordinate(coordinate) {}

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_PLAYER_PLACEHOLDER;
    }

    Player get_player() const {
        return player;
    }

    Coordinate get_coordinate() const {
        return coordinate;
    }
};

#endif //TICTACTOE_WRITEPLAYERPLACEHOLDEREVENT_H
