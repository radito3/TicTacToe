#ifndef TICTACTOE_INPUTREADERWORKER_H
#define TICTACTOE_INPUTREADERWORKER_H

#include <functional>
#include <utility>
#include "Worker.h"
#include "InputReader.h"
#include "events/WritePlayerSymbolEvent.h"

class InputReaderWorker : public Worker {
    InputReader* input_reader;
    std::function<Player()> get_current_player_func;
    std::function<Coordinate()> get_current_coord_func;

public:
    InputReaderWorker(GameEventQueue &eventQueue, InputReader *inputReader,
                      std::function<Player()> getCurrentPlayerFunc,
                      std::function<Coordinate()> getCurrentCoordFunc)
                      : Worker(eventQueue), input_reader(inputReader),
                      get_current_player_func(std::move(getCurrentPlayerFunc)),
                      get_current_coord_func(std::move(getCurrentCoordFunc)) {}

    void handle_event(GameEvent *event) override {
        input_t input = input_reader->read();
        if (input.set_symbol) {
            event_queue.submit_event(new WritePlayerSymbolEvent(get_current_player_func(), get_current_coord_func()));
            return;
        }
        event_queue.submit_event(new MovePlayerPlaceholderEvent(get_current_player_func(), get_current_coord_func(), input.move_direction));
    }

    std::unordered_set<GameEventType> get_supported_event_types() const override {
        return { GameEventType::WAIT_PLAYER_INPUT };
    }
};

#endif //TICTACTOE_INPUTREADERWORKER_H
