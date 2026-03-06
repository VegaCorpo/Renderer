#include "InputHandler.hpp"
#include "raylib.h"

static const std::unordered_map<inputs::Key, inputs::Actions> commands = {
    { {key: KEY_UP, status: inputs::Status::PRESSED }, inputs::Actions::MOVE_UP },
    { {key: KEY_DOWN, status: inputs::Status::PRESSED }, inputs::Actions::MOVE_DOWN },
    { {key: KEY_RIGHT, status: inputs::Status::PRESSED }, inputs::Actions::MOVE_RIGHT },
    { {key: KEY_LEFT, status: inputs::Status::PRESSED }, inputs::Actions::MOVE_LEFT }
};

void inputs::InputHandler::updateKeys()
{
    for (auto &command : commands) {
        if (IsKeyDown(command.first.key)) {
            if (this->_keysHandler[command.first.key] == inputs::Status::PRESSED)
                this->_keysHandler[command.first.key] = inputs::Status::HOVER;
            else
                this->_keysHandler[command.first.key] = inputs::Status::PRESSED;
        } else {
            if (this->_keysHandler[command.first.key] == inputs::Status::RELEASED)
                this->_keysHandler[command.first.key] = inputs::Status::DEFAULT;
            if (this->_keysHandler[command.first.key] == inputs::Status::PRESSED)
                this->_keysHandler[command.first.key] = inputs::Status::RELEASED;
        }
    }
    return;
}

void inputs::InputHandler::getActions(std::list<inputs::Actions> &actions)
{
    this->updateKeys();
    for (auto &command : commands) {
        if (this->_keysHandler[command.first.key] == command.first.status)
            actions.push_back(command.second);
    }
    return;
}
