#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H

#include <utility>
#include <memory>
#include <functional>
#include "Symbol.h"
#include "io/DisplayWriter.h"
#include "io/InputReader.h"

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

    void write_output(std::function<void(DisplayWriter*, const std::string&, Symbol)>&& function) const {
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

    friend std::ostream& operator<<(std::ostream&, const Player&);
};

std::ostream& operator<<(std::ostream& out, const Player& player) {
    out << "{\"id\":\"" << player.id << "\",\"symbol\":" << static_cast<int>(player.symbol) << '}';
    return out;
}

#endif //TICTACTOE_PLAYER_H
