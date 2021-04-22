#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H

#include <utility>
#include <memory>
#include "Symbol.h"
#include "DisplayWriter.h"
#include "InputReader.h"

class Player {
    std::string id;
    Symbol symbol;
    std::shared_ptr<DisplayWriter> writer;
    std::shared_ptr<InputReader> reader;

public:
    Player(std::string id, Symbol symbol, DisplayWriter *writer, InputReader *reader)
            : id(std::move(id)), symbol(symbol), writer(writer), reader(reader) {}

    std::string get_id() const {
        return id;
    }

    Symbol get_symbol() const {
        return symbol;
    }

    template<typename Function>
    void write_output(Function&& function) const {
        function(writer.get(), id, symbol);
    }

    template<typename Rep = int64_t, typename Period = std::ratio<1>>
    input_t read_input(std::chrono::duration<Rep, Period> timeout = std::chrono::seconds(0)) const {
        auto* timeout_reader = dynamic_cast<TimeoutInputReader*>(reader.get());
        if (timeout.count() > 0 && timeout_reader != nullptr) {
            return timeout_reader->read_with_timeout(timeout);
        }
        return reader->read();
    }
};

#endif //TICTACTOE_PLAYER_H
