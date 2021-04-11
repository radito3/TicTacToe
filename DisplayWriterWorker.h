#ifndef TICTACTOE_DISPLAYWRITERWORKER_H
#define TICTACTOE_DISPLAYWRITERWORKER_H

#include <vector>
#include "Worker.h"
#include "DisplayWriter.h"
#include "MatrixCell.h"
#include "events/WritePlayerSymbolEvent.h"
#include "events/WritePlayerPlaceholderEvent.h"
#include "events/MovePlayerPlaceholderEvent.h"

class DisplayWriterWorker : public Worker {
    DisplayWriter* display_writer;
    std::vector<MatrixCell>& game_board;

public:
    DisplayWriterWorker(GameEventQueue &eventQueue, DisplayWriter *displayWriter, std::vector<MatrixCell> &gameBoard)
            : Worker(eventQueue), display_writer(displayWriter), game_board(gameBoard) {}

    void handle_event(GameEvent *event) override {
        switch (event->get_event_type()) {
            case GameEventType::MOVE_PLAYER_PLACEHOLDER: {
                auto *move_placeholder_ev = dynamic_cast<MovePlayerPlaceholderEvent*>(event);
                //check if movement is legal
                move_placeholder_ev->getPlayer().writer_player_placeholder(display_writer,
                                                                           move_placeholder_ev->getStartingCoord());
                break;
            }
            case GameEventType::WRITE_PLAYER_SYMBOL: {
                auto* write_symbol_ev = dynamic_cast<WritePlayerSymbolEvent*>(event);

                break;
            }
            case GameEventType::WRITE_MATRIX:
                display_writer->write_grid();
                break;
            case GameEventType::WRITE_PLAYER_PLACEHOLDER:
                auto* write_placeholder_ev = dynamic_cast<WritePlayerPlaceholderEvent*>(event);

                break;
        }
    }

    std::unordered_set<GameEventType> get_supported_event_types() const override {
        return { GameEventType::WRITE_MATRIX, GameEventType::WRITE_PLAYER_PLACEHOLDER,
                 GameEventType::WRITE_PLAYER_SYMBOL, GameEventType::WRITE_STROKE };
    }

};

#endif //TICTACTOE_DISPLAYWRITERWORKER_H
