#pragma once

#include <queue>
#include <unordered_map>
#include "raylib.h"
#include "types/types.hpp"

namespace inputs {

    enum class Status { DEFAULT, PRESSED, RELEASED };

    struct Key {
            KeyboardKey key;
            Status status;
    };

    static const std::unordered_map<KeyboardKey, std::unordered_map<inputs::Status, common::Action>> commands = {
        {KEY_UP, {{inputs::Status::PRESSED, common::Action::MOVE_CAMERA_UP}}},
        {KEY_DOWN, {{inputs::Status::PRESSED, common::Action::MOVE_CAMERA_DOWN}}},
        {KEY_RIGHT, {{inputs::Status::PRESSED, common::Action::MOVE_CAMERA_RIGHT}}},
        {KEY_LEFT, {{inputs::Status::PRESSED, common::Action::MOVE_CAMERA_LEFT}}}};

    class InputHandler {
        public:
            InputHandler() = default;
            ~InputHandler() = default;

            // getActions detects inputs and adds actions in list given in parameters.
            void updateActions(std::queue<common::Action>& actions);

        private:
            // updateKeys checks keyboards input status and updates _keysHandler.
            inputs::Status _updateKeys(KeyboardKey key);

            std::unordered_map<KeyboardKey, inputs::Status> _keysHandler;
    };
} // namespace inputs
