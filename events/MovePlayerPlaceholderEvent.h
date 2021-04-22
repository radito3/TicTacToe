#ifndef TICTACTOE_MOVEPLAYERPLACEHOLDEREVENT_H
#define TICTACTOE_MOVEPLAYERPLACEHOLDEREVENT_H

#include "../Player.h"
#include "GameEvent.h"

class MovePlayerPlaceholderEvent : public GameEvent {
    Player player;
    Coordinate starting_coord;
    MoveDirection direction;
    Coordinate desired_coord;

public:
    MovePlayerPlaceholderEvent(Player player, Coordinate startingCoord, MoveDirection direction)
            : player(std::move(player)), starting_coord(startingCoord), direction(direction),
            desired_coord({-1, -1}) {}

    MovePlayerPlaceholderEvent(Player player, Coordinate startingCoord, Coordinate desiredCoord)
            : player(std::move(player)), starting_coord(startingCoord), direction(MoveDirection::INVALID),
            desired_coord(desiredCoord) {}

    GameEventType get_event_type() const noexcept override {
        return GameEventType::MOVE_PLAYER_PLACEHOLDER;
    }

    Player getPlayer() const {
        return player;
    }

    Coordinate getStartingCoord() const {
        return starting_coord;
    }

    MoveDirection getDirection() const {
        return direction;
    }

    Coordinate getDesiredCoord() const {
        return desired_coord;
    }
};

#endif //TICTACTOE_MOVEPLAYERPLACEHOLDEREVENT_H
