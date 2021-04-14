#ifndef TICTACTOE_DISPLAYWRITER_H
#define TICTACTOE_DISPLAYWRITER_H

#include "Coordinate.h"
#include "Direction.h"
#include "Player.h"

class DisplayWriter {
public:
    virtual ~DisplayWriter() = default;

    virtual void write_grid() const = 0;

    virtual void clear_cell_at(const Coordinate&) const = 0;

    virtual void write_symbol(Symbol, const Coordinate&) const = 0;

    virtual void write_placeholder_for(Symbol, const Coordinate&) const = 0;

    virtual void write_stroke(const Coordinate&, StrokeDirection) const = 0;

    virtual void write_victory_msg_for(const std::string &) const = 0;

    virtual void write_draw_msg() const = 0;

};

#endif //TICTACTOE_DISPLAYWRITER_H
