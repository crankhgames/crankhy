#include "SDL2/SDL.h"

#include "game.h"
#include "graphics/camera.h"
#include "graphics/texture-manager.h"
#include "math/vector.h"

namespace Crankhy {

    template <int M, int N>
    struct Tilemap {
        Vector position;
        int tiles [M][N]{};
        float cellSize;
        Spritesheet* spritesheet;
    };

    template <int M, int N>
    void draw_tilemap(Tilemap<M, N> *tilemap){
        EntityID camEntity = Game::get().getCamera();
        CameraComponent& camComponent = Game::get().getECS().getComponent<CameraComponent>(camEntity);
        TransformComponent& camTransform = Game::get().getECS().getComponent<TransformComponent>(camEntity);

        for (int i = 0; i < M; i++){
            for (int j = 0; j < N; j++){
                tilemap->spritesheet->changeSprite(tilemap->tiles[i][j]);
                TransformComponent t = TransformComponent{

                    .position = tilemap->position +  Vector(i, j) *  tilemap->cellSize,
                    .scale = Vector(tilemap->cellSize, tilemap->cellSize),
                };
                SDL_Rect dRect = localToScreen(camTransform, camComponent, t);
                draw(tilemap->spritesheet, dRect, false, false);
            }
        }
    }
}