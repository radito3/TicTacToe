#ifndef TICTACTOE_WRITEPLAYERPLACEHOLDEREVENT_H
#define TICTACTOE_WRITEPLAYERPLACEHOLDEREVENT_H

#include "GameEvent.h"

class WritePlayerPlaceholderEvent : public GameEvent {
    const Player& current_player;
    const Coordinate& current_coordinate;

public:
    WritePlayerPlaceholderEvent(const Player &currentPlayer, const Coordinate &currentCoordinate)
            : current_player(currentPlayer), current_coordinate(currentCoordinate) {}

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_PLAYER_PLACEHOLDER;
    }

    const Player &get_current_player() const {
        return current_player;
    }

    const Coordinate &get_current_coordinate() const {
        return current_coordinate;
    }
};

#endif //TICTACTOE_WRITEPLAYERPLACEHOLDEREVENT_H
