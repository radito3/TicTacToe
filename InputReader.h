#ifndef TICTACTOE_INPUTREADER_H
#define TICTACTOE_INPUTREADER_H

#include <future>
#include <chrono>
#include "Direction.h"

enum class input_type_t {
    DIRECTIONAL, POSITIONAL, SET
};

struct input_t {
    MoveDirection move_direction;
    bool set_symbol;
    Coordinate coord;
    input_type_t type;

    explicit input_t(MoveDirection move_dir)
            : move_direction(move_dir), set_symbol(false), coord({-1, -1}), type(input_type_t::DIRECTIONAL) {}

    explicit input_t(bool set_symbol)
            : move_direction(MoveDirection::INVALID), set_symbol(set_symbol), coord({-1, -1}),
              type(input_type_t::SET) {}

    explicit input_t(Coordinate coord)
            : move_direction(MoveDirection::INVALID), set_symbol(false), coord(coord),
              type(input_type_t::POSITIONAL) {}
};

class InputReader {
public:
    virtual ~InputReader() = default;

    virtual input_t read() const = 0;
};

class timeout_exception : public std::runtime_error {
public:
    timeout_exception() : runtime_error("timeout") {}
};

class TimeoutInputReader : public InputReader {
public:

    template<typename Rep, typename Period>
    input_t read_with_timeout(const std::chrono::duration<Rep, Period>& duration) {
        std::future<input_t> read_result = std::async(std::launch::async, read);
        if (read_result.wait_for(duration) == std::future_status::timeout) {
            throw timeout_exception();
        }
        return read_result.get();
    }
};

#endif //TICTACTOE_INPUTREADER_H
