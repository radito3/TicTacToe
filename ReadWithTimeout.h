#ifndef TICTACTOE_READWITHTIMEOUT_H
#define TICTACTOE_READWITHTIMEOUT_H

#include <thread>
#include <chrono>
#include "GameEventQueue.h"
#include "InputReader.h"
#include "events/SwitchPlayerEvent.h"
#include "events/WriteTimeoutPromptEvent.h"

class ReadWithTimeout {
    GameEventQueue& event_queue;
    InputReader* input_reader;

    std::condition_variable timer;
    std::mutex t_mutex;

public:
    ReadWithTimeout(GameEventQueue& queue, InputReader* reader) : event_queue(queue), input_reader(reader) {}

    std::pair<bool, input_t> operator()() {
        using namespace std::chrono_literals;
        input_t input(false);
        bool has_timed_out = false;

        std::thread reader([&input, this]() {
            input = input_reader->read();
            timer.notify_one();
        });
        reader.detach();

        std::unique_lock<std::mutex> lock(t_mutex);
        if (timer.wait_for(lock, 30s) == std::cv_status::timeout) {
            event_queue.submit_event(new WriteTimeoutPromptEvent);
            has_timed_out = true;
        }
        if (has_timed_out && timer.wait_for(lock, 30s) == std::cv_status::timeout) {
            event_queue.submit_event(new SwitchPlayerEvent);
            return { true, input_t(false) };
        }
        return { false, input };
    }
};

#endif //TICTACTOE_READWITHTIMEOUT_H
