#ifndef TICTACTOE_WRITEPLAYERSYMBOLEVENT_H
#define TICTACTOE_WRITEPLAYERSYMBOLEVENT_H

#include <functional>
#include <utility>
#include "Player.h"
#include "Coordinate.h"
#include "GameEvent.h"

class WritePlayerSymbolEvent : public GameEvent {
    std::function<const Player &()> get_current_player_func;
    std::function<Coordinate()> get_current_coord_func;

public:
    WritePlayerSymbolEvent(std::function<const Player &()> getCurrentPlayerFunc,
                           std::function<Coordinate()> getCurrentCoordFunc)
            : get_current_player_func(std::move(getCurrentPlayerFunc)),
            get_current_coord_func(std::move(getCurrentCoordFunc)) {}

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_PLAYER_SYMBOL;
    }
};

#endif //TICTACTOE_WRITEPLAYERSYMBOLEVENT_H
