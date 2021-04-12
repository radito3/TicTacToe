#ifndef TICTACTOE_WRITESTROKEEVENT_H
#define TICTACTOE_WRITESTROKEEVENT_H

#include "GameEvent.h"
#include "../Direction.h"
#include "../Coordinate.h"

class WriteStrokeEvent : public GameEvent {
    Coordinate coord;
    StrokeDirection direction;

public:
    WriteStrokeEvent(Coordinate coord, StrokeDirection direction) : coord(coord), direction(direction) {}

    GameEventType get_event_type() const noexcept override {
        return GameEventType::WRITE_STROKE;
    }

    Coordinate get_coord() const {
        return coord;
    }

    StrokeDirection get_direction() const {
        return direction;
    }
};

#endif //TICTACTOE_WRITESTROKEEVENT_H
