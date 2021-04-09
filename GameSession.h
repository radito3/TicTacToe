#ifndef TICTACTOE_GAMESESSION_H
#define TICTACTOE_GAMESESSION_H

#include <random>
#include <vector>
#include <thread>
#include <functional>
#include "GameEventQueue.h"
#include "DisplayWriter.h"
#include "InputReader.h"
#include "Player.h"
#include "MatrixCell.h"
#include "PlayerMovePlaceholderEvent.h"

class GameSession {
    GameEventQueue event_queue;
    unsigned player_turn;
    std::vector<MatrixCell> game_board;
    Player player1;
    Player player2;

    std::vector<std::thread> game_threads;

    DisplayWriter* display_writer;
    InputReader* input_reader;

    using CState = MatrixCell::State;

    Coordinate get_current_coordinate() const {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                int matrix_index = row * 3 + col;
                if (game_board[matrix_index].is_current) {
                    return { row, col };
                }
            }
        }
        return { -1, -1 };
    }

    const Player& get_current_player() const {
        return player_turn == 0 ? player1 : player2;
    }

    void initiate() {
        //boot up threads (display writer thread, input reader thread, event handlers dispatcher thread [, timeout handling thread])
        //send event for writing the game matrix
        //send event for writing the current player's placeholder
    }

    void send_initial_events() {

    }

public:
    GameSession(Player player1, Player player2,
                DisplayWriter* display_writer,
                InputReader* input_reader) : game_board(9, MatrixCell(CState::EMPTY)),
                                             player1(std::forward<Player>(player1)),
                                             player2(std::forward<Player>(player2)),
                                             display_writer(display_writer),
                                             input_reader(input_reader)
    {
        player_turn = std::mt19937(std::random_device()())() % 1;
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

    //[in a later implementation stage]
    //each player turn will have a 1 minute timeout
    //30 sec after the beginning of a turn, if there hasn't been any input, a popup will appear
    // "your turn will timeout due to inactivity" (console version will be a blinking red symbol)
    //if no action is taken, and the whole minute expires, the turns switch
};

#endif //TICTACTOE_GAMESESSION_H
