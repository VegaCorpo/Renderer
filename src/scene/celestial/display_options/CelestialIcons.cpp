#include "CelestialIcons.hpp"

render::CelestialIcons::CelestialIcons() : ADisplayOption(NAME, DESCRIPTION, Layer::SCREEN_2D)
{}

//! to implement to save cameraview and if changed recompute icon
void render::CelestialIcons::update(const std::size_t /*entity*/, const CelestialBody& /*body*/)
{}

void render::CelestialIcons::draw(const std::size_t /*entity*/, const CelestialBody& /*body*/,
                                  const render::CameraView& /*cameraView*/, GLRenderer& /*renderer*/) const
{}

void render::CelestialIcons::reset()
{}
