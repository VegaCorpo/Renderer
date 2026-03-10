#pragma once

namespace render {
    constexpr float EARTH_MANTISSA = 5.97;
    constexpr int EARTH_EXPONENT = 24;
    constexpr float MOON_MANTISSA = 7.35;
    constexpr int MOON_EXPONENT = 22;
    constexpr float SUN_MANTISSA = 1.98;
    constexpr int SUN_EXPONENT = 30;

    // ----------------------------
    // 1. Distance scale (km → UA)
    // ----------------------------
    constexpr float UA = 149'597'870.700f; // km
    constexpr float POSITION_SCALE = 1.0f / UA; // 1 UA = 1.0 unité scène

    // ----------------------------
    // 2. Real radius (km)
    // ----------------------------
    constexpr float SUN_RADIUS = 696'340.f;
    constexpr float EARTH_RADIUS = 6'371.f;
    constexpr float MOON_RADIUS = 1'737.4f;

    constexpr float SUN_POS = 0.f;
    constexpr float EARTH_POS = 149597870.f;
    constexpr float MOON_POS = 149213470.f;

    // ----------------------------
    // 3. Visual size scale (indépendant des positions)
    // ----------------------------
    constexpr float SIZE_SCALE = 500.0f / UA; // ~15x plus grand que réel

    constexpr float DIST_EARTH_MOON = 384400.f;
    constexpr float DIST_EARTH_MOON_SCALED = DIST_EARTH_MOON * SIZE_SCALE / 20;

    // ----------------------------
    // 4. Final render radius
    // ----------------------------
    constexpr float SUN_RADIUS_RENDER = SUN_RADIUS * SIZE_SCALE / 20;
    constexpr float EARTH_RADIUS_RENDER = EARTH_RADIUS * SIZE_SCALE;
    constexpr float MOON_RADIUS_RENDER = MOON_RADIUS * SIZE_SCALE;
} // namespace render
