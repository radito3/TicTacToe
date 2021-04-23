#ifndef TICTACTOE_WRITETIMEOUTPROMPTHANDLER_H
#define TICTACTOE_WRITETIMEOUTPROMPTHANDLER_H

#include "DisplayEventHandler.h"
#include "../events/WriteTimeoutPromptEvent.h"

class WriteTimeoutPromptHandler : public DisplayEventHandler {
public:

    void handle_event(GameEvent *event) override {
        auto* timeout_ev = dynamic_cast<WriteTimeoutPromptEvent*>(event);

        timeout_ev->get_player().write_output([](auto* writer, auto& p_id, auto p_symbol) {
            writer->write_temp_msg("Your turn will end in 30 seconds due to inactivity");
        });
    }
};

#endif //TICTACTOE_WRITETIMEOUTPROMPTHANDLER_H
