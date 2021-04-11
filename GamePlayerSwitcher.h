#ifndef TICTACTOE_GAMEPLAYERSWITCHER_H
#define TICTACTOE_GAMEPLAYERSWITCHER_H

#include <functional>
#include <utility>
#include <unordered_set>
#include "Worker.h"

class GamePlayerSwitcher : public Worker {
    std::function<void()> switch_player_func;

public:
    GamePlayerSwitcher(GameEventQueue &eventQueue, std::function<void()> switchPlayerFunc)
            : Worker(eventQueue), switch_player_func(std::move(switchPlayerFunc)) {}

    void handle_event(GameEvent *event) override {
        switch_player_func();
    }

    std::unordered_set<GameEventType> get_supported_event_types() const override {
        return { GameEventType::SWITCH_PLAYER };
    }

};

#endif //TICTACTOE_GAMEPLAYERSWITCHER_H
