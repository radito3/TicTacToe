#ifndef TICTACTOE_DISPLAYWRITERWORKER_H
#define TICTACTOE_DISPLAYWRITERWORKER_H

#include "Worker.h"
#include "DisplayWriter.h"

class DisplayWriterWorker : public Worker {
    DisplayWriter* display_writer;

public:
    DisplayWriterWorker(std::condition_variable &cond, GameEventQueue &eventQueue, DisplayWriter *displayWriter)
            : Worker(cond, eventQueue), display_writer(displayWriter) {}

    void handle_event(GameEvent *event) override {
        switch (event->get_event_type()) {
            case GameEventType::MOVE_PLAYER_PLACEHOLDER:
                auto* move_placeholder_ev = dynamic_cast<MovePlayerPlaceholderEvent*>(event);
                //check if movement is legal
                event->getPlayer().writer_player_placeholder(display_writer, event->getStartingCoord());
                break;
            case GameEventType::WRITE_MATRIX:
                display_writer->write_grid();
                break;
            case GameEventType::WRITE_PLAYER_SYMBOL:
                auto* write_symbol_ev = dynamic_cast<WritePlayerSymbolEvent*>(event);
                //handle
                break;
            default:
                break;
        }
    }

};

#endif //TICTACTOE_DISPLAYWRITERWORKER_H
