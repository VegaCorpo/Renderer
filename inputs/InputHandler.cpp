#include "InputHandler.hpp"

static const std::unordered_map<KeyboardKey, std::unordered_map<inputs::Status, common::Action>> commands = {
    { KEY_UP, { inputs::Status::PRESSED, common::Action::MOVE_CAMERA_UP } },
    { KEY_DOWN, { inputs::Status::PRESSED, common::Action::MOVE_CAMERA_DOWN } },
    { KEY_RIGHT, { inputs::Status::PRESSED, common::Action::MOVE_CAMERA_RIGHT } },
    { KEY_LEFT, { inputs::Status::PRESSED, common::Action::MOVE_CAMERA_LEFT } }
};

inputs::Status inputs::InputHandler::_updateKeys(KeyboardKey key)
{
    inputs::Status keyStatus = this->_keysHandler[key];

    if (IsKeyDown(key)) {
        return inputs::Status::PRESSED;
    } else {
        if (keyStatus == inputs::Status::PRESSED)
            return inputs::Status::RELEASED;
    }
    return inputs::Status::DEFAULT;
}

void inputs::InputHandler::getActions(std::vector<common::Action> &actions)
{
    for (const auto &[key, command] : commands) {
        inputs::Status newKeyStatus = this->_updateKeys(key);
        this->_keysHandler[key] = newKeyStatus;
        auto it = command.find(newKeyStatus);
        if (it != command.end())
            actions.push_back(*it);
    }
}
