#pragma once

#include <unordered_map>
#include <list>

using KeycodeRaylib = int;

namespace inputs {

    enum class Status {
        DEFAULT,
        PRESSED,
        RELEASED
    };

    typedef struct Key_s {
        KeycodeRaylib key;
        Status status;
    } Key;

    class InputHandler {
        public:
            InputHandler() = default;
            ~InputHandler() = default;

            // getActions detects inputs and adds actions in list given in parameters.
            void getActions(std::list<common::Action> &actions);
        private:
            // updateKeys checks keyboards input status and updates _keysHandler.
            void updateKeys();

            std::unordered_map<KeycodeRaylib, inputs::Status> _keysHandler;
    };
}
