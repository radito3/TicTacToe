#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H

#include <utility>
#include "Symbol.h"

class Player {
    std::string id;
    Symbol symbol;

public:
    Player(std::string id, Symbol symbol) : id(std::move(id)), symbol(symbol) {}

    std::string get_id() const {
        return id;
    }

    Symbol get_symbol() const {
        return symbol;
    }
};

#endif //TICTACTOE_PLAYER_H
