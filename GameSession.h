#ifndef TICTACTOE_GAMESESSION_H
#define TICTACTOE_GAMESESSION_H

#include <random>
#include <vector>
#include "GameEventQueue.h"

class GameSession {
    GameEventQueue event_queue;
    int player_one_id;
    int player_two_id;
    int player_turn;
    bool is_finished;
    std::vector<int> game_state;

public:
    GameSession(int player_one_id, int player_two_id) : player_one_id(player_one_id),
                                                        player_two_id(player_two_id),
                                                        is_finished(false),
                                                        game_state(9, 0)
    {
        player_turn = std::mt19937(std::random_device()()) % 1;
    }

    
    //each player turn will have a 1 minute timeout
    //30 sec after the beginning of a turn, if there hasn't been any input, a popup will appear
    // "your turn will timeout due to inactivity" (console version will be a blinking red symbol)
    //if no action is taken, and the whole minute expires, the turns switch
};

#endif //TICTACTOE_GAMESESSION_H
