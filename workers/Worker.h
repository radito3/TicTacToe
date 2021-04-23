#ifndef TICTACTOE_WORKER_H
#define TICTACTOE_WORKER_H

#include <unordered_set>
#include "../GameEventQueue.h"
#include "../events/ShutdownEvent.h"

class Worker {

    void process_event_and_handle_exceptions(GameEvent* event) {
        try {
            handle_event(event);
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            event_queue->submit_event(new ShutdownEvent);
        }
    }

protected:
    GameEventQueue* event_queue;

public:
    explicit Worker(GameEventQueue *eventQueue) : event_queue(eventQueue) {}

    void operator()() {
        auto supported_event_types = get_supported_event_types();
        while (true) {
            auto* event = event_queue->get_next_event();
            if (event->get_event_type() == GameEventType::SHUTDOWN) {
                break;
            }
            if (supported_event_types.find(event->get_event_type()) != supported_event_types.end()) {
                event_queue->pop_event();
                process_event_and_handle_exceptions(event);
                delete event;
            }
        }
    }

    virtual void handle_event(GameEvent* event) = 0;

    virtual std::unordered_set<GameEventType> get_supported_event_types() const = 0;

};

#endif //TICTACTOE_WORKER_H
