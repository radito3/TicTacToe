#ifndef TICTACTOE_GAMESESSION_H
#define TICTACTOE_GAMESESSION_H

#include <random>
#include <vector>
#include <thread>
#include "GameEventQueue.h"
#include "DisplayWriter.h"
#include "DisplayWriterWorker.h"
#include "InputReaderWorker.h"
#include "GamePlayerSwitcher.h"
#include "GameEndConditionChecker.h"
#include "InputReader.h"
#include "Player.h"
#include "MatrixCell.h"
#include "events/WriteMatrixEvent.h"
#include "events/WritePlayerPlaceholderEvent.h"

class GameSession {
    std::vector<MatrixCell> game_board;
    unsigned player_turn;
    Player player1;
    Player player2;

    GameEventQueue event_queue;
    std::vector<std::thread> game_threads;

    DisplayWriter* display_writer;
    InputReader* input_reader;

    Coordinate get_current_coordinate() const {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (game_board[row * 3 + col].is_current) {
                    return { col, row };
                }
            }
        }
        throw std::runtime_error("Invalid game state");
    }

    Player get_current_player() const {
        return player_turn == 0 ? player1 : player2;
    }

    void switch_current_player() {
        player_turn = player_turn == 0 ? 1 : 0;
    }

    void initiate() {
        game_threads.emplace_back(DisplayWriterWorker(event_queue, display_writer, game_board));
        game_threads.emplace_back(InputReaderWorker(event_queue, input_reader,
                                                    std::bind(&GameSession::get_current_player, this),
                                                    std::bind(&GameSession::get_current_coordinate, this)));
        game_threads.emplace_back(GameEndConditionChecker(event_queue, game_board));
        game_threads.emplace_back(GamePlayerSwitcher(event_queue, std::bind(&GameSession::switch_current_player, this),
                                                     std::bind(&GameSession::get_current_player, this),
                                                     std::bind(&GameSession::get_current_coordinate, this)));
    }

    void send_initial_events() {
        event_queue.submit_event(new WriteMatrixEvent);
        event_queue.submit_event(new WritePlayerPlaceholderEvent(get_current_player(), get_current_coordinate()));
    }

public:
    GameSession(Player player1, Player player2,
                DisplayWriter* display_writer,
                InputReader* input_reader) : game_board(9, MatrixCell()),
                                             player1(std::forward<Player>(player1)),
                                             player2(std::forward<Player>(player2)),
                                             display_writer(display_writer),
                                             input_reader(input_reader)
    {
        player_turn = std::mt19937(std::random_device()())() % 2;
        game_board.front().is_current = true;
    }

    ~GameSession() {
        delete display_writer;
        delete input_reader;
    }

    void play() {
        initiate();
        send_initial_events();
        for (auto& th : game_threads) {
            th.join();
        }
    }
};

#endif //TICTACTOE_GAMESESSION_H
