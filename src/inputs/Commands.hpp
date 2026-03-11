#pragma once

#include <raylib.h>
#include <unordered_map>
#include "types/types.hpp"

namespace inputs {
    enum class Status { DEFAULT, PRESSED, PRESSED_REPEAT, RELEASED };

    struct Key {
            KeyboardKey key;
            Status status;
    };

    static const std::unordered_map<KeyboardKey, std::unordered_map<inputs::Status, common::Action>> commands = {
        {KEY_Z,
         {
             {inputs::Status::PRESSED, common::Action::MOVE_CAMERA_FORWARD},
             {inputs::Status::RELEASED, common::Action::MOVE_CAMERA_BACKWARD},
         }},
        {KEY_S,
         {
             {inputs::Status::PRESSED, common::Action::MOVE_CAMERA_BACKWARD},
             {inputs::Status::RELEASED, common::Action::MOVE_CAMERA_FORWARD},
         }},
        {KEY_Q,
         {
             {inputs::Status::PRESSED, common::Action::MOVE_CAMERA_LEFT},
             {inputs::Status::RELEASED, common::Action::MOVE_CAMERA_RIGHT},
         }},
        {KEY_D,
         {
             {inputs::Status::PRESSED, common::Action::MOVE_CAMERA_RIGHT},
             {inputs::Status::RELEASED, common::Action::MOVE_CAMERA_LEFT},
         }},
        {KEY_SPACE,
         {
             {inputs::Status::PRESSED, common::Action::MOVE_CAMERA_UP},
             {inputs::Status::RELEASED, common::Action::MOVE_CAMERA_DOWN},
         }},
        {KEY_LEFT_CONTROL,
         {
             {inputs::Status::PRESSED, common::Action::MOVE_CAMERA_DOWN},
             {inputs::Status::RELEASED, common::Action::MOVE_CAMERA_UP},
         }},
        {KEY_UP,
         {
             {inputs::Status::PRESSED, common::Action::ROTATE_CAMERA_UP},
             {inputs::Status::RELEASED, common::Action::ROTATE_CAMERA_DOWN},
         }},
        {KEY_DOWN,
         {
             {inputs::Status::PRESSED, common::Action::ROTATE_CAMERA_DOWN},
             {inputs::Status::RELEASED, common::Action::ROTATE_CAMERA_UP},
         }},
        {KEY_LEFT,
         {
             {inputs::Status::PRESSED, common::Action::ROTATE_CAMERA_LEFT},
             {inputs::Status::RELEASED, common::Action::ROTATE_CAMERA_RIGHT},
         }},
        {KEY_RIGHT,
         {
             {inputs::Status::PRESSED, common::Action::ROTATE_CAMERA_RIGHT},
             {inputs::Status::RELEASED, common::Action::ROTATE_CAMERA_LEFT},
         }},
    };

    static const std::unordered_map<KeyboardKey, KeyboardKey> AzertyToQwertyKeys = {
        {KEY_Z, KEY_W},
        {KEY_Q, KEY_A},
    };

    static KeyboardKey convertAzerty(KeyboardKey key)
    {
        auto it = AzertyToQwertyKeys.find(key);

        if (it != AzertyToQwertyKeys.end()) {
            return it->second;
        }
        return key;
    }
} // namespace inputs
