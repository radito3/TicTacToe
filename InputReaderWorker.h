#ifndef TICTACTOE_INPUTREADERWORKER_H
#define TICTACTOE_INPUTREADERWORKER_H

#include "Worker.h"
#include "InputReader.h"
#include "WritePlayerSymbolEvent.h"

class InputReaderWorker : public Worker {
    InputReader* input_reader;

public:
    InputReaderWorker(std::condition_variable &cond, GameEventQueue &eventQueue, InputReader *inputReader)
            : Worker(cond, eventQueue), input_reader(inputReader) {}

    void handle_event(GameEvent *event) override {
        if (event->get_event_type() == GameEventType::WAIT_PLAYER_INPUT) {
            input_t input = input_reader->read();
            if (input.set_symbol) {
                event_queue.submit_event(new WritePlayerSymbolEvent(...));
            }
            //...
        }
    }
};

#endif //TICTACTOE_INPUTREADERWORKER_H
