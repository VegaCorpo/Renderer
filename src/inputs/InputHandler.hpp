#pragma once

#include <queue>
#include <raylib.h>
#include "Commands.hpp"
#include "types/types.hpp"

namespace inputs {
    static const std::unordered_map<bool (*)(int), Status> keyStates = {
        {IsKeyPressed, inputs::Status::PRESSED},
        {IsKeyPressedRepeat, inputs::Status::PRESSED_REPEAT},
        {IsKeyReleased, inputs::Status::RELEASED},
    };

    class InputHandler {
        public:
            InputHandler() = default;
            ~InputHandler() = default;

            // getActions detects inputs and adds actions in list given in parameters.
            static void updateActions(std::queue<common::Action>& actions);

        private:
            // updateKeys checks keyboards input status and updates _keysHandler.
            static inputs::Status _updateKey(KeyboardKey key);
    };
} // namespace inputs
