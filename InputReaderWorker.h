#ifndef TICTACTOE_INPUTREADERWORKER_H
#define TICTACTOE_INPUTREADERWORKER_H

#include <functional>
#include <utility>
#include "Worker.h"
#include "InputReader.h"
#include "events/WritePlayerSymbolEvent.h"
#include "events/SwitchPlayerEvent.h"
#include "events/WriteTimeoutPromptEvent.h"

class InputReaderWorker : public Worker {
    std::function<Player()> get_current_player_func;
    std::function<Coordinate()> get_current_coord_func;

    GameEvent* parse_input(const Player& current_player, const input_t& input) {
        switch (input.type) {
            case input_type_t::DIRECTIONAL:
                return new MovePlayerPlaceholderEvent(current_player, get_current_coord_func(), input.move_direction);
            case input_type_t::POSITIONAL:
                return new MovePlayerPlaceholderEvent(current_player, get_current_coord_func(), input.coord);
            case input_type_t::SET:
                return new WritePlayerSymbolEvent(current_player, get_current_coord_func());
        }
    }

public:
    InputReaderWorker(GameEventQueue &eventQueue,
                      std::function<Player()> getCurrentPlayerFunc,
                      std::function<Coordinate()> getCurrentCoordFunc)
                      : Worker(eventQueue),
                      get_current_player_func(std::move(getCurrentPlayerFunc)),
                      get_current_coord_func(std::move(getCurrentCoordFunc)) {}

    void handle_event(GameEvent *event) override {
        using namespace std::chrono_literals;
        auto current_player = get_current_player_func();
        input_t input(false);
        bool has_timed_out = false;

        try {
            input = current_player.read_input(30s);
        } catch (const timeout_exception& timeout) {
            event_queue.submit_event(new WriteTimeoutPromptEvent(current_player));
            has_timed_out = true;
        }
        if (has_timed_out) {
            try {
                input = current_player.read_input(30s);
            } catch (const timeout_exception& timeout) {
                event_queue.submit_event(new SwitchPlayerEvent);
                return;
            }
        }
        event_queue.submit_event(parse_input(current_player, input));
    }

    std::unordered_set<GameEventType> get_supported_event_types() const override {
        return { GameEventType::WAIT_PLAYER_INPUT };
    }
};

#endif //TICTACTOE_INPUTREADERWORKER_H
