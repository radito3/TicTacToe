#ifndef TICTACTOE_DISPLAYWRITERWORKER_H
#define TICTACTOE_DISPLAYWRITERWORKER_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "Worker.h"
#include "../MatrixCell.h"
#include "../display_handlers/DisplayEventHandler.h"
#include "../display_handlers/MovePlayerPlaceholderHandler.h"
#include "../display_handlers/WritePlayerSymbolHandler.h"
#include "../display_handlers/WriteMatrixHandler.h"
#include "../display_handlers/WritePlayerPlaceholderHandler.h"
#include "../display_handlers/WriteStrokeHandler.h"
#include "../display_handlers/WriteTimeoutPromptHandler.h"
#include "../display_handlers/WriteVictoryMessageHandler.h"
#include "../display_handlers/WriteDrawMessageHandler.h"

class DisplayWriterWorker : public Worker {
    std::unordered_map<GameEventType, std::shared_ptr<DisplayEventHandler>> handlers;

public:
    DisplayWriterWorker(GameEventQueue *eventQueue, std::vector<MatrixCell> *gameBoard,
                        const Player& p1, const Player& p2) : Worker(eventQueue),
            handlers({
                 {GameEventType::MOVE_PLAYER_PLACEHOLDER, std::make_shared<MovePlayerPlaceholderHandler>(gameBoard, eventQueue)},
                 {GameEventType::WRITE_PLAYER_SYMBOL, std::make_shared<WritePlayerSymbolHandler>(gameBoard, eventQueue, p1, p2)},
                 {GameEventType::WRITE_MATRIX, std::make_shared<WriteMatrixHandler>(p1, p2)},
                 {GameEventType::WRITE_PLAYER_PLACEHOLDER, std::make_shared<WritePlayerPlaceholderHandler>(gameBoard, eventQueue)},
                 {GameEventType::WRITE_STROKE, std::make_shared<WriteStrokeHandler>(p1, p2)},
                 {GameEventType::WRITE_TIMEOUT_PROMPT, std::make_shared<WriteTimeoutPromptHandler>()},
                 {GameEventType::WRITE_VICTORY_MSG, std::make_shared<WriteVictoryMessageHandler>(eventQueue, p1, p2)},
                 {GameEventType::WRITE_DRAW_MSG, std::make_shared<WriteDrawMessageHandler>(eventQueue, p1, p2)}
            }) {}

    void handle_event(GameEvent *event) override {
        handlers.at(event->get_event_type())->handle_event(event);
    }

    std::unordered_set<GameEventType> get_supported_event_types() const override {
        return { GameEventType::WRITE_MATRIX, GameEventType::WRITE_PLAYER_PLACEHOLDER,
                 GameEventType::WRITE_PLAYER_SYMBOL, GameEventType::MOVE_PLAYER_PLACEHOLDER,
                 GameEventType::WRITE_TIMEOUT_PROMPT, GameEventType::WRITE_STROKE, GameEventType::WRITE_DRAW_MSG,
                 GameEventType::WRITE_VICTORY_MSG };
    }

};

#endif //TICTACTOE_DISPLAYWRITERWORKER_H
