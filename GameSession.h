#ifndef TICTACTOE_GAMESESSION_H
#define TICTACTOE_GAMESESSION_H

#include <random>
#include <vector>
#include <thread>
#include "GameEventQueue.h"
#include "io/DisplayWriter.h"
#include "io/InputReader.h"
#include "workers/DisplayWriterWorker.h"
#include "workers/InputReaderWorker.h"
#include "workers/GamePlayerSwitcher.h"
#include "workers/GameEndConditionChecker.h"
#include "Player.h"
#include "MatrixCell.h"
#include "events/WriteMatrixEvent.h"
#include "events/WritePlayerPlaceholderEvent.h"
#include "events/ShutdownEvent.h"

class GameSession {
    std::vector<MatrixCell> game_board;
    unsigned player_turn;
    Player player1;
    Player player2;

    GameEventQueue event_queue;
    std::vector<std::thread> game_threads;

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
        game_threads.emplace_back(DisplayWriterWorker(&event_queue, &game_board, player1, player2));
        game_threads.emplace_back(InputReaderWorker(&event_queue,std::bind(&GameSession::get_current_player, this),
                                                    std::bind(&GameSession::get_current_coordinate, this)));
        game_threads.emplace_back(GameEndConditionChecker(&event_queue, &game_board));
        game_threads.emplace_back(GamePlayerSwitcher(&event_queue, std::bind(&GameSession::switch_current_player, this),
                                                     std::bind(&GameSession::get_current_player, this),
                                                     std::bind(&GameSession::get_current_coordinate, this)));
    }

    void send_initial_events() {
        event_queue.submit_event(new WriteMatrixEvent);
        event_queue.submit_event(new WritePlayerPlaceholderEvent(get_current_player(), get_current_coordinate()));
    }

public:
    GameSession(Player player1, Player player2) : game_board(9, MatrixCell()),
            player1(std::forward<Player>(player1)), player2(std::forward<Player>(player2))
    {
        player_turn = std::mt19937(std::random_device()())() % 2;
        game_board.front().is_current = true;
    }

    void play() {
        initiate();
        send_initial_events();
        for (auto& th : game_threads) {
            th.join();
        }
    }

    void initiate_shutdown() {
        event_queue.submit_event(new ShutdownEvent);
    }

    friend std::ostream& operator<<(std::ostream&, const GameSession&);
};

std::ostream& operator<<(std::ostream& out, const GameSession& session) {
    out << "{\"game_board\":[";
    for (int i = 0; i < session.game_board.size(); ++i) {
        const MatrixCell& cell = session.game_board[i];
        out << "{\"state\":" << static_cast<int>(cell.state) << ",\"is_current\":" << cell.is_current << '}';
        if (i != session.game_board.size() - 1) {
            out << ',';
        }
    }
    out << "],\"player_turn\":" << session.player_turn;
    out << ",\"player_1\":" << session.player1 << ",\"player_2\":" << session.player2 << '}';
    return out;
}

#endif //TICTACTOE_GAMESESSION_H
