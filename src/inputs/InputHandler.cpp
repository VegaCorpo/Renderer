#include "InputHandler.hpp"

inputs::Status inputs::InputHandler::_updateKey(KeyboardKey key)
{
    KeyboardKey fixedKey = convertAzerty(key);

    for (const auto& [checkStatus, status] : keyStates) {
        if (checkStatus(fixedKey)) {
            return status;
        }
    }
    return inputs::Status::DEFAULT;
}

void inputs::InputHandler::updateActions(std::queue<common::Action>& actions)
{
    for (const auto& [key, command] : commands) {
        inputs::Status newKeyStatus = _updateKey(key);

        if (command.find(newKeyStatus) != command.end()) {
            actions.push(command.at(newKeyStatus));
        }
    }
}
