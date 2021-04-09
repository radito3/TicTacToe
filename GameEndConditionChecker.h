#ifndef TICTACTOE_GAMEENDCONDITIONCHECKER_H
#define TICTACTOE_GAMEENDCONDITIONCHECKER_H

class GameEndConditionChecker {


public:

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
};

#endif //TICTACTOE_GAMEENDCONDITIONCHECKER_H
