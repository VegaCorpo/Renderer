#pragma once

#include <array>
#include <types/types.hpp>

namespace render {
    static const std::array<common::Action, 11> sceneActions = {
        common::Action::MOVE_CAMERA_FORWARD, common::Action::MOVE_CAMERA_BACKWARD, common::Action::MOVE_CAMERA_DOWN,
        common::Action::MOVE_CAMERA_UP,      common::Action::MOVE_CAMERA_LEFT,     common::Action::MOVE_CAMERA_RIGHT,
        common::Action::ROTATE_CAMERA_UP,    common::Action::ROTATE_CAMERA_DOWN,   common::Action::ROTATE_CAMERA_LEFT,
        common::Action::ROTATE_CAMERA_RIGHT, common::Action::CHANGE_RESCALE_MODE,
    };
} // namespace render
