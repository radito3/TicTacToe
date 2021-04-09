#ifndef TICTACTOE_WORKER_H
#define TICTACTOE_WORKER_H

#include <condition_variable>
#include "GameEventQueue.h"

class Worker {
    std::condition_variable& cond;
    std::mutex mutex;

protected:
    GameEventQueue& event_queue;

public:
    Worker(std::condition_variable &cond, GameEventQueue &eventQueue) : cond(cond), event_queue(eventQueue) {}

    void operator()() {
        while (true) {
            std::unique_lock<std::mutex> lock(mutex);
            cond.wait(lock);

            auto* event = event_queue.peek_next_event();
            if (event->get_event_type() == GameEventType::SHUTDOWN) {
                break;
            }

            handle_event(event);

            event_queue.pop_event();
            delete event;
        }
    }

    virtual void handle_event(GameEvent* event) = 0;

};

#endif //TICTACTOE_WORKER_H
