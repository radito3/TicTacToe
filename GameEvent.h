#ifndef TICTACTOE_GAMEEVENT_H
#define TICTACTOE_GAMEEVENT_H

class GameEvent {
    int player_id;
    //...
public:
    explicit GameEvent(int playerId) : player_id(playerId) {}

    int get_player_id() const {
        return player_id;
    }

    //...
};

#endif //TICTACTOE_GAMEEVENT_H
