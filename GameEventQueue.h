#ifndef TICTACTOE_GAMEEVENTQUEUE_H
#define TICTACTOE_GAMEEVENTQUEUE_H

#include <queue>
#include <mutex>
#include "GameEvent.h"

class GameEventQueue {
    std::queue<GameEvent> queue;
    std::mutex q_mutex;

    typedef std::lock_guard<std::mutex> lock_t;

public:
    GameEventQueue() = default;

    bool submit_event(const GameEvent& event) {
        lock_t lock(q_mutex);
        if (/*event rejection policy*/ queue.size() == 1) { //check if should reject
            return false;
        }
        queue.push(event);
        return true;
    }

    GameEvent& get_next_event() {
        //block until there is an event

        return queue.back();
    }

    // <event> peek_next_event()
};

#endif //TICTACTOE_GAMEEVENTQUEUE_H
