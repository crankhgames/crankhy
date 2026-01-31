#pragma once
#include "SDL2/SDL.h"
#include "math/vector.h"
#include "scene/components.h"


namespace Crankhy{


SDL_Rect localToScreen(TransformComponent& cameraTransform, CameraComponent& camera, TransformComponent& transform);

}