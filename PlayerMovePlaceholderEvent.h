#ifndef TICTACTOE_PLAYERMOVEPLACEHOLDEREVENT_H
#define TICTACTOE_PLAYERMOVEPLACEHOLDEREVENT_H

#include "Player.h"
#include "GameEvent.h"

class PlayerMovePlaceholderEvent : public GameEvent {
    Player player;
    Coordinate starting_coord;
    MoveDirection direction;

public:
    PlayerMovePlaceholderEvent(Player player, const Coordinate &startingCoord, const MoveDirection &direction)
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

    //should this method be here or in another "EventHandler" class
    void handle(std::vector<MatrixCell>& game_board) {
        //if the movement cant't be done (there is a symbol in the spot where the player wants to move
        // his placeholder could be colored red for 500 milliseconds (0.5 secs)
    }

};

#endif //TICTACTOE_PLAYERMOVEPLACEHOLDEREVENT_H
