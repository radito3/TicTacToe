#ifndef TICTACTOE_DISPLAYWRITER_H
#define TICTACTOE_DISPLAYWRITER_H

#include "Coordinate.h"
#include "Direction.h"

class DisplayWriter {
public:
    virtual ~DisplayWriter() = default;

    virtual void write_grid() const = 0;

    virtual void write_cross(const Coordinate&) const = 0;

    virtual void write_circle(const Coordinate&) const = 0;

    virtual void write_stroke(const Coordinate&, Direction) const = 0;

};

#endif //TICTACTOE_DISPLAYWRITER_H
