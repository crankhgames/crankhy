#include "graphics/camera.h"


namespace Crankhy{


Vector screenToLocal(TransformComponent& cameraTransform, CameraComponent& camera, Vector& vector){
    return Vector(vector.x / camera.pixelsToUnit.x, vector.y / camera.pixelsToUnit.y) + cameraTransform.position;
}

SDL_Rect localToScreen(TransformComponent& cameraTransform, CameraComponent& camera, TransformComponent& transform){
    Vector newPos = transform.position - cameraTransform.position;
    return SDL_Rect{
        .x=(int)(newPos.x * camera.pixelsToUnit.x),
        .y=(int)(newPos.y * camera.pixelsToUnit.y),
        .w=(int)(transform.scale.x * camera.pixelsToUnit.x),
        .h=(int)(transform.scale.y * camera.pixelsToUnit.y),
    };
}

}