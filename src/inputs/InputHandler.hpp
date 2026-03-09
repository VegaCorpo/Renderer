#pragma once

#include <functional>
#include <queue>
#include <unordered_map>
#include "raylib.h"
#include "types/types.hpp"

namespace inputs {

    enum class Status { DEFAULT, PRESSED, PRESSED_REPEAT, RELEASED };

    struct Key {
            KeyboardKey key;
            Status status;
    };

    static const std::unordered_map<KeyboardKey, std::unordered_map<inputs::Status, common::Action>> commands = {
        {KEY_UP, {{inputs::Status::PRESSED, common::Action::MOVE_CAMERA_UP}}},
        {KEY_DOWN, {{inputs::Status::PRESSED, common::Action::MOVE_CAMERA_DOWN}}},
        {KEY_RIGHT, {{inputs::Status::PRESSED, common::Action::MOVE_CAMERA_RIGHT}}},
        {KEY_LEFT, {{inputs::Status::PRESSED, common::Action::MOVE_CAMERA_LEFT}}}};

    static const std::unordered_map<bool (*)(int), Status> keyStates = {
        {IsKeyPressed, inputs::Status::PRESSED},
        {IsKeyPressedRepeat, inputs::Status::PRESSED_REPEAT},
        {IsKeyReleased, inputs::Status::RELEASED}};

    class InputHandler {
        public:
            InputHandler() = default;
            ~InputHandler() = default;

            // getActions detects inputs and adds actions in list given in parameters.
            static void updateActions(std::queue<common::Action>& actions);

        private:
            // updateKeys checks keyboards input status and updates _keysHandler.
            static inputs::Status _updateKeys(KeyboardKey key);
    };
} // namespace inputs
