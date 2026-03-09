#include "InputHandler.hpp"

inputs::Status inputs::InputHandler::_updateKeys(KeyboardKey key)
{
    inputs::Status keyStatus = this->_keysHandler[key];

    if (IsKeyDown(key))
        return inputs::Status::PRESSED;
    if (keyStatus == inputs::Status::PRESSED)
        return inputs::Status::RELEASED;
    return inputs::Status::DEFAULT;
}

void inputs::InputHandler::getActions(std::queue<common::Action>& actions)
{
    for (const auto& [key, command] : commands) {
        inputs::Status newKeyStatus = this->_updateKeys(key);

        this->_keysHandler[key] = newKeyStatus;
        if (command.find(newKeyStatus) != command.end())
            actions.push(command.at(newKeyStatus));
    }
}
