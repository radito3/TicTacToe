#ifndef TICTACTOE_MOVEPLAYERPLACEHOLDERHANDLER_H
#define TICTACTOE_MOVEPLAYERPLACEHOLDERHANDLER_H

#include <vector>
#include <thread>
#include <chrono>
#include "../MatrixCell.h"
#include "../GameEventQueue.h"
#include "DisplayEventHandler.h"
#include "../events/MovePlayerPlaceholderEvent.h"
#include "../events/WaitPlayerInputEvent.h"

class MovePlayerPlaceholderHandler : public DisplayEventHandler {
    std::vector<MatrixCell>* game_board;
    GameEventQueue* event_queue;

    bool is_movement_legal(const MovePlayerPlaceholderEvent* const& event) const {
        if (event->getDirection() == MoveDirection::INVALID) {
            return is_movement_legal(event->getDesiredCoord());
        }
        return is_movement_legal(event->getStartingCoord(), event->getDirection());
    }

    bool is_movement_legal(const Coordinate& coord, MoveDirection move_dir) const {
        auto new_coord = get_new_coordinate(coord, move_dir);
        return game_board->at(new_coord.y * 3 + new_coord.x).state == MatrixCell::State::EMPTY;
    }

    bool is_movement_legal(const Coordinate& coord) const {
        return game_board->at(coord.y * 3 + coord.x).state == MatrixCell::State::EMPTY;
    }

    static Coordinate get_new_coordinate(const MovePlayerPlaceholderEvent* const& event) {
        if (event->getDirection() == MoveDirection::INVALID) {
            return event->getDesiredCoord();
        }
        return get_new_coordinate(event->getStartingCoord(), event->getDirection());
    }

    static Coordinate get_new_coordinate(const Coordinate& current, MoveDirection move_dir) {
        switch (move_dir) {
            case MoveDirection::UP: {
                int new_y = current.y == 0 ? 2 : (current.y - 1);
                return { current.x, new_y };
            }
            case MoveDirection::DOWN: {
                int new_y = current.y == 2 ? 0 : (current.y + 1);
                return { current.x, new_y };
            }
            case MoveDirection::LEFT: {
                int new_x = current.x == 0 ? 2 : (current.x - 1);
                return { new_x, current.y };
            }
            case MoveDirection::RIGHT: {
                int new_x = current.x == 2 ? 0 : (current.x + 1);
                return { new_x, current.y };
            }
            default:
                throw std::runtime_error("Invalid move direction");
        }
    }

    static MatrixCell::State get_placeholder(const Player& player) {
        return player.get_symbol() == Symbol::CIRCLE ? MatrixCell::State::CIRCLE_PLACEHOLDER : MatrixCell::State::CROSS_PLACEHOLDER;
    }

    Coordinate get_current_coordinate() const {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (game_board->at(row * 3 + col).is_current) {
                    return { col, row };
                }
            }
        }
        throw std::runtime_error("Invalid game state");
    }

    void flash_player_placeholder(const Player& current_player) {
        auto current_coord = get_current_coordinate();

        current_player.write_output([&](auto* writer, auto& p_id, auto p_symbol) {
            writer->flash_placeholder(p_symbol, current_coord);
        });
    }

    void clear_active_cells() {
        for (auto& cell : *game_board) {
            cell.is_current = false;
        }
    }

public:
    MovePlayerPlaceholderHandler(std::vector<MatrixCell> *gameBoard, GameEventQueue *eventQueue)
            : game_board(gameBoard), event_queue(eventQueue) {}

    void handle_event(GameEvent *event) override {
        auto* move_ev = dynamic_cast<MovePlayerPlaceholderEvent*>(event);
        auto current_player = move_ev->getPlayer();

        if (!is_movement_legal(move_ev)) {
            flash_player_placeholder(current_player);
            event_queue->submit_event(new WaitPlayerInputEvent);
            return;
        }
        auto old_coord = get_current_coordinate();
        game_board->at(old_coord.y * 3 + old_coord.x).state = MatrixCell::State::EMPTY;

        clear_active_cells();

        auto new_coord = get_new_coordinate(move_ev);
        game_board->at(new_coord.y * 3 + new_coord.x).is_current = true;
        game_board->at(new_coord.y * 3 + new_coord.x).state = get_placeholder(move_ev->getPlayer());

        current_player.write_output([&](auto* writer, auto& p_id, auto p_symbol) {
            writer->clear_cell_at(old_coord);
            writer->write_placeholder_for(p_symbol, new_coord);
        });

        event_queue->submit_event(new WaitPlayerInputEvent);
    }
};

#endif //TICTACTOE_MOVEPLAYERPLACEHOLDERHANDLER_H
