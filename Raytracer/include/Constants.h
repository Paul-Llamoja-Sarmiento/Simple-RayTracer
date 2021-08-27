#pragma once

// Canvas parameters (image) - Pixels
constexpr float ASPECT_RATIO = 16.0f / 9.0f;
constexpr int CANVAS_HEIGHT = 200;
constexpr int CANVAS_WIDTH = static_cast<int>(CANVAS_HEIGHT * ASPECT_RATIO);

// Camera parameters (viewport) - Coordinates System
constexpr float VIEWPORT_HEIGHT = 2.0f;
constexpr float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * ASPECT_RATIO;
constexpr float FOCAL_LENGTH = 1.0f;

const Vec3f ORIGIN =     Vec3f(0.0f           , 0.0f            , 0.0f);
const Vec3f HORIZONTAL = Vec3f(VIEWPORT_WIDTH , 0.0f            , 0.0f);
const Vec3f VERTICAL =   Vec3f(0.0f           , VIEWPORT_HEIGHT , 0.0f);

const Vec3f LOWER_LEFT_CORNER = ORIGIN -
                                (HORIZONTAL / 2) - 
                                (VERTICAL / 2) -
                                Vec3f(0.0f , 0.0f , FOCAL_LENGTH);