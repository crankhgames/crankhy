#pragma once
#include "SDL2/SDL.h"
#include "math/vector.h"
#include "scene/components.h"


namespace Crankhy{


Vector screenToLocal(TransformComponent& cameraTransform, CameraComponent& camera, Vector& vector);
SDL_Rect localToScreen(TransformComponent& cameraTransform, CameraComponent& camera, TransformComponent& transform);

}