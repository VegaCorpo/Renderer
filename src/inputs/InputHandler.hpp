#pragma once

#include <unordered_map>
#include <vector>
#include "raylib.h"
#include "types/types.hpp"

namespace inputs {

    enum class Status { DEFAULT, PRESSED, RELEASED };

    struct Key {
            KeyboardKey key;
            Status status;
    };

    class InputHandler {
        public:
            InputHandler() = default;
            ~InputHandler() = default;

            // getActions detects inputs and adds actions in list given in parameters.
            void getActions(std::vector<common::Action>& actions);

        private:
            // updateKeys checks keyboards input status and updates _keysHandler.
            inputs::Status _updateKeys(KeyboardKey key);

            std::unordered_map<KeyboardKey, inputs::Status> _keysHandler;
    };
} // namespace inputs
