#ifndef TICTACTOE_WRITEPLAYERSYMBOLEVENT_H
#define TICTACTOE_WRITEPLAYERSYMBOLEVENT_H

#include <functional>
#include <utility>
#include "../Player.h"
#include "../Coordinate.h"
#include "GameEvent.h"

class WritePlayerSymbolEvent : public GameEvent {
    const Player& current_player;
    const Coordinate& current_coord;

public:
    WritePlayerSymbolEvent(const Player &currentPlayer, const Coordinate &currentCoord)
            : current_player(currentPlayer), current_coord(currentCoord) {}

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_PLAYER_SYMBOL;
    }

    const Player &get_current_player() const {
        return current_player;
    }

    const Coordinate &get_current_coord() const {
        return current_coord;
    }
};

#endif //TICTACTOE_WRITEPLAYERSYMBOLEVENT_H
