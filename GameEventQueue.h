#ifndef TICTACTOE_GAMEEVENTQUEUE_H
#define TICTACTOE_GAMEEVENTQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include "GameEvent.h"

class GameEventQueue {
    std::queue<GameEvent*> queue;
    std::mutex q_mutex;

    typedef std::unique_lock<std::mutex> lock_t;

    std::condition_variable empty_cond;

public:
    GameEventQueue() = default;

    void submit_event(GameEvent* event) {
        lock_t lock(q_mutex);
        queue.push(std::forward<GameEvent*>(event));
        empty_cond.notify_all();
    }

    GameEvent* retrieve_next_event() {
        lock_t lock(q_mutex);
        empty_cond.wait(lock, [&]() { return !queue.empty(); });

        GameEvent* ev = queue.front();
        queue.pop();
        return ev;
    }

    const GameEvent* peek_next_event() {
        lock_t lock(q_mutex);
        empty_cond.wait(lock, [&]() { return !queue.empty(); });

        return queue.front();
    }
};

#endif //TICTACTOE_GAMEEVENTQUEUE_H
