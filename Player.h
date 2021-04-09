#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H

#include <utility>
#include "DisplayWriter.h"

class Player {
public:
    typedef void(DisplayWriter::*symbol_writer)(const Coordinate&) const;
    typedef void(DisplayWriter::*placeholder_writer)(const Coordinate&) const;

private:
    std::string id;
    symbol_writer symbol_writer_func;
    placeholder_writer placeholder_writer_func;

public:
    Player(std::string id, symbol_writer s_writer, placeholder_writer p_writer) :
        id(std::move(id)), symbol_writer_func(s_writer), placeholder_writer_func(p_writer) {}

    std::string get_id() const {
        return id;
    }

    void write_player_symbol(const DisplayWriter* display_writer, const Coordinate& coord) const {
        (display_writer->*symbol_writer_func)(coord);
    }

    void writer_player_placeholder(const DisplayWriter* display_writer, const Coordinate& coord) const {
        (display_writer->*placeholder_writer_func)(coord);
    }

};

#endif //TICTACTOE_PLAYER_H
