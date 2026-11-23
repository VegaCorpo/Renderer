#include "ADisplayOption.hpp"

render::ADisplayOption::ADisplayOption(const std::string_view name, const std::string_view description,
                                       const Layer layer) :
    _name(name), _description(description), _layer(layer), _enabled(DEFAULT_ENABLED), _params()
{}

bool render::ADisplayOption::is2D() const
{
    return this->_layer == Layer::SCREEN_2D;
}

bool render::ADisplayOption::isEnabled() const
{
    return this->_enabled;
}

void render::ADisplayOption::setEnabled(const bool enabled)
{
    if (this->_enabled == enabled) {
        return;
    }
    this->_enabled = enabled;

    // Restart from scratch so a trail doesn't join its old and new points
    if (enabled) {
        this->reset();
    }
}

std::vector<common::DisplayOptionParam> render::ADisplayOption::params() const
{
    std::vector<common::DisplayOptionParam> params;

    params.reserve(this->_params.size());
    for (const auto& param : this->_params) {
        params.push_back({.name = param.name, .description = param.description, .value = param.get()});
    }
    return params;
}

void render::ADisplayOption::setParams(const std::vector<common::DisplayOptionParam>& params)
{
    for (const auto& param : params) {
        for (const auto& bound : this->_params) {
            if (bound.name == param.name) {
                bound.set(param.value);
                break;
            }
        }
    }
}

common::DisplayOption render::ADisplayOption::toDisplayOption(const common::DisplayOptionId id) const
{
    return {
        .id = id,
        .enabled = this->_enabled,
        .name = this->_name,
        .description = this->_description,
        .params = this->params(),
    };
}
