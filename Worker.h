#ifndef TICTACTOE_WORKER_H
#define TICTACTOE_WORKER_H

#include <unordered_set>
#include "GameEventQueue.h"

class Worker {
protected:
    GameEventQueue& event_queue;

public:
    explicit Worker(GameEventQueue &eventQueue) : event_queue(eventQueue) {}

    void operator()() {
        while (true) {
            auto* event = event_queue.get_next_event();
            if (event->get_event_type() == GameEventType::SHUTDOWN) {
                break;
            }
            auto supported_event_types = get_supported_event_types();
            if (supported_event_types.find(event->get_event_type()) != supported_event_types.end()) {
                event_queue.pop_event();
                handle_event(event);
                delete event;
            }
        }
    }

    virtual void handle_event(GameEvent* event) = 0;

    virtual std::unordered_set<GameEventType> get_supported_event_types() const = 0;

};

#endif //TICTACTOE_WORKER_H
