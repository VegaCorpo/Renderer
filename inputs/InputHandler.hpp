#pragma once

#include <unordered_map>
#include <list>

using KeycodeRaylib = int;

namespace inputs {

    enum class Status {
        DEFAULT,
        PRESSED,
        HOVER,
        RELEASED
    };

    typedef struct Key_s {
        KeycodeRaylib key;
        Status status;
    } Key;

    enum class Actions {
        NONE,
        MOVE_CAMERA_UP,
        MOVE_CAMERA_DOWN,
        MOVE_CAMERA_RIGHT,
        MOVE_CAMERA_LEFT,
        CHANGE_SELECTION,
        CHANGE_SELECTION_REVERSED
    };

    class InputHandler {
        public:
            InputHandler() = default;
            ~InputHandler() = default;

            void getActions(std::list<inputs::Actions> &actions);
        private:
            std::unordered_map<KeycodeRaylib, inputs::Status> _keysHandler;
    };
}
