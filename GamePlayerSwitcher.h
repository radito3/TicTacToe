#ifndef TICTACTOE_GAMEPLAYERSWITCHER_H
#define TICTACTOE_GAMEPLAYERSWITCHER_H

#include <functional>
#include <utility>
#include <unordered_set>
#include "Worker.h"
#include "events/WritePlayerPlaceholderEvent.h"

class GamePlayerSwitcher : public Worker {
    std::function<void()> switch_player_func;
    std::function<Player()> get_current_player_func;
    std::function<Coordinate()> get_current_coord_func;

public:
    GamePlayerSwitcher(GameEventQueue &eventQueue, std::function<void()> switchPlayerFunc,
                       std::function<Player()> getCurrentPlayerFunc,
                       std::function<Coordinate()> getCurrentCoordFunc)
                       : Worker(eventQueue),
                       switch_player_func(std::move(switchPlayerFunc)),
                       get_current_player_func(std::move(getCurrentPlayerFunc)),
                       get_current_coord_func(std::move(getCurrentCoordFunc)) {}

    void handle_event(GameEvent *event) override {
        switch_player_func();
        event_queue.submit_event(new WritePlayerPlaceholderEvent(get_current_player_func(), get_current_coord_func()));
    }

    std::unordered_set<GameEventType> get_supported_event_types() const override {
        return { GameEventType::SWITCH_PLAYER };
    }

};

#endif //TICTACTOE_GAMEPLAYERSWITCHER_H
