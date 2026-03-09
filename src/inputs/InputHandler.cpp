#include "InputHandler.hpp"

inputs::Status inputs::InputHandler::_updateKeys(KeyboardKey key)
{
    for (const auto& [checkStatus, status] : keyStates) {
        if (checkStatus(key))
            return status;
    }
    return inputs::Status::DEFAULT;
}

void inputs::InputHandler::updateActions(std::queue<common::Action>& actions)
{
    for (const auto& [key, command] : commands) {
        inputs::Status newKeyStatus = _updateKeys(key);

        if (command.find(newKeyStatus) != command.end())
            actions.push(command.at(newKeyStatus));
    }
}
