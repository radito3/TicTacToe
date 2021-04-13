#ifndef TICTACTOE_WRITEPLAYERSYMBOLEVENT_H
#define TICTACTOE_WRITEPLAYERSYMBOLEVENT_H

#include <functional>
#include <utility>
#include "../Player.h"
#include "../Coordinate.h"
#include "GameEvent.h"

class WritePlayerSymbolEvent : public GameEvent {
    Player current_player;
    Coordinate current_coord;

public:
    WritePlayerSymbolEvent(Player currentPlayer, Coordinate currentCoord)
            : current_player(currentPlayer), current_coord(currentCoord) {}

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_PLAYER_SYMBOL;
    }

    Player get_current_player() const {
        return current_player;
    }

    Coordinate get_current_coord() const {
        return current_coord;
    }
};

#endif //TICTACTOE_WRITEPLAYERSYMBOLEVENT_H
