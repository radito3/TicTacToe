#ifndef TICTACTOE_GAMEEVENTQUEUE_H
#define TICTACTOE_GAMEEVENTQUEUE_H

#include <queue>
#include <mutex>
#include "GameEvent.h"

class GameEventQueue {
    std::queue<GameEvent> event_queue;
    std::mutex ev_queue_mutex;

    typedef std::lock_guard<std::mutex> lock_t;

public:
    GameEventQueue() = default;

    bool submit_event(const GameEvent& event) {
        lock_t lock(ev_queue_mutex);
        if (/*event rejection policy*/ event_queue.size() == 1) { //check if should reject
            return false;
        }
        event_queue.push(event);
        return true;
    }

    GameEvent& get_next_event() {
        //block until there is an event

        return event_queue.back();
    }

    // <event> peek_next_event()
};

#endif //TICTACTOE_GAMEEVENTQUEUE_H
