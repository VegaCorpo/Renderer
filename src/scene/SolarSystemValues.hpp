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
    constexpr float SCALE = 10.0f / UA; // 1 UA = 1.0 unité scène

    // ----------------------------
    // 2. Real radius (km)
    // ----------------------------
    constexpr float SUN_RADIUS = 696'342.f;
    constexpr float EARTH_RADIUS = 6'378.137f;
    constexpr float MOON_RADIUS = 1'737.4f;

    constexpr float SUN_POS = 0.f;
    constexpr float EARTH_POS = 149597870.f;
    constexpr float MOON_POS = 149213470.f;

    // ----------------------------
    // 3. Visual size scale (indépendant des positions)
    // ----------------------------
    constexpr float SIZE_SCALE_MULTIPLIER = 250.f;

    constexpr float VISUAL_MIN_SEPARATION_MULT = 1.0f;
    constexpr float SHRINK_FACTOR = 0.85f;
    constexpr int RELAX_ITERATIONS = 8;
} // namespace render
