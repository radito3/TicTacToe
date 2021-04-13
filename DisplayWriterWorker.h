#ifndef TICTACTOE_DISPLAYWRITERWORKER_H
#define TICTACTOE_DISPLAYWRITERWORKER_H

#include <vector>
#include "Worker.h"
#include "DisplayWriter.h"
#include "MatrixCell.h"
#include "events/WritePlayerSymbolEvent.h"
#include "events/WritePlayerPlaceholderEvent.h"
#include "events/MovePlayerPlaceholderEvent.h"
#include "events/CheckEndConditionEvent.h"
#include "events/ShutdownEvent.h"
#include "events/WriteStrokeEvent.h"
#include "events/WriteVictoryMessageEvent.h"
#include "events/WaitPlayerInputEvent.h"

class DisplayWriterWorker : public Worker {
    DisplayWriter* display_writer;
    std::vector<MatrixCell>& game_board;

    static MatrixCell::State get_state(const Player& player) {
        return player.get_symbol() == Symbol::CIRCLE ? MatrixCell::State::CIRCLE : MatrixCell::State::CROSS;
    }

    static MatrixCell::State get_placeholder(const Player& player) {
        return player.get_symbol() == Symbol::CIRCLE ? MatrixCell::State::CIRCLE_PLACEHOLDER : MatrixCell::State::CROSS_PLACEHOLDER;
    }

    bool is_movement_legal(const Coordinate& coord, MoveDirection move_dir) const {
        auto new_coord = get_new_coordinate(coord, move_dir);
        return game_board[new_coord.y * 3 + new_coord.x].state == MatrixCell::State::EMPTY;
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
                return { -1, -1 };
        }
    }

    Coordinate get_current_coordinate() const {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (game_board[row * 3 + col].is_current) {
                    return { col, row };
                }
            }
        }
        return { -1, -1 };
    }

    void clear_active_cells() {
        for (auto& cell : game_board) {
            cell.is_current = false;
        }
    }

    int get_next_available_pos(const Coordinate& coord) const {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (game_board[row * 3 + col].state == MatrixCell::State::EMPTY) {
                    return row * 3 + col;
                }
            }
        }
        return 0;
    }

    void write_player_symbol(WritePlayerSymbolEvent* write_symbol_ev) {
        auto player = write_symbol_ev->get_current_player();
        auto coord = write_symbol_ev->get_current_coord();
        int matrix_index = coord.y * 3 + coord.x;

        if (game_board[matrix_index].state != get_placeholder(player)) {
            throw std::runtime_error("current coordinate doesn't match current player's placeholder");
        }
        game_board[matrix_index].state = get_state(player);
        display_writer->clear_cell_at(coord);
        display_writer->write_symbol(player.get_symbol(), coord);

        clear_active_cells();
        game_board[get_next_available_pos(coord)].is_current = true;

        event_queue.submit_event(new CheckEndConditionEvent(player));
    }

public:
    DisplayWriterWorker(GameEventQueue &eventQueue, DisplayWriter *displayWriter, std::vector<MatrixCell> &gameBoard)
            : Worker(eventQueue), display_writer(displayWriter), game_board(gameBoard) {}

    void handle_event(GameEvent *event) override {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"
        switch (event->get_event_type()) {
            case GameEventType::MOVE_PLAYER_PLACEHOLDER: {
                auto *move_placeholder_ev = dynamic_cast<MovePlayerPlaceholderEvent*>(event);
                if (!is_movement_legal(move_placeholder_ev->getStartingCoord(), move_placeholder_ev->getDirection())) {
                    event_queue.submit_event(new WaitPlayerInputEvent);
                    break;
                }
                display_writer->clear_cell_at(get_current_coordinate());
                clear_active_cells();
                auto new_coord = get_new_coordinate(move_placeholder_ev->getStartingCoord(), move_placeholder_ev->getDirection());
                game_board[new_coord.y * 3 + new_coord.x].is_current = true;
                display_writer->write_placeholder_for(move_placeholder_ev->getPlayer().get_symbol(), new_coord);
                break;
            }
            case GameEventType::WRITE_PLAYER_SYMBOL:
                write_player_symbol(dynamic_cast<WritePlayerSymbolEvent*>(event));
                break;
            case GameEventType::WRITE_MATRIX:
                display_writer->write_grid();
                break;
            case GameEventType::WRITE_PLAYER_PLACEHOLDER: {
                auto *write_placeholder_ev = dynamic_cast<WritePlayerPlaceholderEvent*>(event);
                display_writer->write_placeholder_for(write_placeholder_ev->get_player().get_symbol(),
                                                      write_placeholder_ev->get_coordinate());
                event_queue.submit_event(new WaitPlayerInputEvent);
                break;
            }
            case GameEventType::WRITE_STROKE: {
                auto *write_stroke_ev = dynamic_cast<WriteStrokeEvent*>(event);
                display_writer->write_stroke(write_stroke_ev->get_coord(), write_stroke_ev->get_direction());
                break;
            }
            case GameEventType::WRITE_VICTORY_MSG: {
                auto *write_victory_msg_ev = dynamic_cast<WriteVictoryMessageEvent*>(event);
                display_writer->write_victory_msg_for(write_victory_msg_ev->get_player_id());
                event_queue.submit_event(new ShutdownEvent);
                break;
            }
            case GameEventType::WRITE_DEADLOCK_MSG:
                display_writer->write_deadlock_msg();
                event_queue.submit_event(new ShutdownEvent);
                break;
        }
#pragma clang diagnostic pop
    }

    std::unordered_set<GameEventType> get_supported_event_types() const override {
        return { GameEventType::WRITE_MATRIX, GameEventType::WRITE_PLAYER_PLACEHOLDER,
                 GameEventType::WRITE_PLAYER_SYMBOL, GameEventType::MOVE_PLAYER_PLACEHOLDER,
                 GameEventType::WRITE_STROKE, GameEventType::WRITE_DEADLOCK_MSG, GameEventType::WRITE_VICTORY_MSG };
    }

};

#endif //TICTACTOE_DISPLAYWRITERWORKER_H
