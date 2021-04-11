#ifndef TICTACTOE_MOVEPLAYERPLACEHOLDEREVENT_H
#define TICTACTOE_MOVEPLAYERPLACEHOLDEREVENT_H

#include "../Player.h"
#include "GameEvent.h"

class MovePlayerPlaceholderEvent : public GameEvent {
    Player player;
    Coordinate starting_coord;
    MoveDirection direction;

public:
    MovePlayerPlaceholderEvent(Player player, const Coordinate &startingCoord, const MoveDirection &direction)
            : player(std::move(player)), starting_coord(startingCoord), direction(direction) {}

    GameEventType get_event_type() const noexcept override {
        return GameEventType::MOVE_PLAYER_PLACEHOLDER;
    }

    const Player &getPlayer() const {
        return player;
    }

    const Coordinate &getStartingCoord() const {
        return starting_coord;
    }

    MoveDirection getDirection() const {
        return direction;
    }
};

#endif //TICTACTOE_MOVEPLAYERPLACEHOLDEREVENT_H
