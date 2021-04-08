#ifndef TICTACTOE_GAMESESSION_H
#define TICTACTOE_GAMESESSION_H

#include <random>
#include <vector>
#include "GameEventQueue.h"
#include "DisplayWriter.h"
#include "Player.h"
#include "MatrixCell.h"
#include "PlayerMovePlaceholderEvent.h"

//don't make this a God-class
class GameSession {
    GameEventQueue event_queue;
    unsigned player_turn;
    bool is_finished;
    std::vector<MatrixCell> game_board;
    DisplayWriter* display_writer;
    Player player1;
    Player player2;

    using CState = MatrixCell::State;

    static MoveDirection parse_move_direction(char ch) {
        switch (ch) {
            case 'w':
                return MoveDirection::UP;
            case 's':
                return MoveDirection::DOWN;
            case 'a':
                return MoveDirection::LEFT;
            case 'd':
                return MoveDirection::RIGHT;
            default:
                return MoveDirection::INVALID;
        }
    }

    //move to appropriate class
    void wait_for_player_input() {
        //move cursor to the side before waiting for input
        char ch;
        while (std::cin >> ch) {
            //reset cursor position

            Coordinate current_coord = get_current_coordinate();
            Player current_player = get_current_player();
            //send input to handler
            if (ch == 'q') {
                //send write symbol event
            }
            MoveDirection move_dir = parse_move_direction(ch);
            if (move_dir == MoveDirection::INVALID) {
                //tell player
            }
            event_queue.submit_event(new PlayerMovePlaceholderEvent(current_player, current_coord, move_dir));
        }
    }

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

public:
    GameSession(DisplayWriter* display_writer, Player player1, Player player2) : is_finished(false),
                                                                                 game_board(9, MatrixCell(CState::EMPTY)),
                                                                                 display_writer(display_writer),
                                                                                 player1(std::forward<Player>(player1)),
                                                                                 player2(std::forward<Player>(player2))
    {
        player_turn = std::mt19937(std::random_device()())() % 1;
        game_board.front().is_current = true;
    }

    ~GameSession() {
        delete display_writer;
    }

    //this method will initiate the game, send the initial events, wait for the end condition and join the threads
    void play() {
        initiate();



        display_writer->write_grid();
        get_current_player().writer_player_placeholder(display_writer, get_current_coordinate());

        wait_for_player_input();

        GameEvent* ev = event_queue.retrieve_next_event();
        if (ev->get_event_type() == GameEventType::MOVE_PLAYER_PLACEHOLDER) {
            //dispatch to appropriate handler
            // in handler ...
            auto* event = dynamic_cast<PlayerMovePlaceholderEvent*>(ev);
            event->getPlayer().writer_player_placeholder(display_writer, event->getStartingCoord());
            delete event;
        }
    }

    //[in a later implementation stage]
    //each player turn will have a 1 minute timeout
    //30 sec after the beginning of a turn, if there hasn't been any input, a popup will appear
    // "your turn will timeout due to inactivity" (console version will be a blinking red symbol)
    //if no action is taken, and the whole minute expires, the turns switch
};

#endif //TICTACTOE_GAMESESSION_H
