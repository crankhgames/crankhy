#include "scene/scene.h"
#include "game.h"



namespace Crankhy{

    void spawnBlock(){

        EntityID block = Game::get().getECS().createEntity();

        float randomRadius = rand() / (float)RAND_MAX * 45 + 15;
        float randomX = rand() / (float)RAND_MAX * 700 + 50;
        float randomY = rand() / (float)RAND_MAX * 500 + 50;

        TransformComponent bTransform;
        bTransform.position = Vector(randomX, randomY);
        bTransform.scale = Vector(randomRadius*2, randomRadius*2);
        Game::get().getECS().addComponent(block, bTransform);

        TextureRendererComponent bTextRenderer;
        bTextRenderer.sprite = new Sprite("assets/sprites/player-sprite.png");
        Game::get().getECS().addComponent(block, bTextRenderer);

        VelocityComponent bVelocity;
        bVelocity.velocity = Vector();
        Game::get().getECS().addComponent(block, bVelocity);

        RectColliderComponent bCollider;
        bCollider.bounds = {randomRadius*2, randomRadius*2};
        bCollider.isStatic = true;
        Game::get().getECS().addComponent<ColliderComponent>(block, bCollider);
    }

    void MainScene::initializeEntities() {
        for (int i = 0; i < 250; i++){
            spawnBlock();
        }

        EntityID player = Game::get().getECS().createEntity();

        TransformComponent pTransform;
        pTransform.position = Vector(400, 300);
        pTransform.scale = Vector(50, 50);
        Game::get().getECS().addComponent(player, pTransform);

        TextureRendererComponent pTexRenderer;
        pTexRenderer.sprite = new Sprite("assets/sprites/logo.png");
        Game::get().getECS().addComponent(player, pTexRenderer);

        VelocityComponent pVelocity;
        pVelocity.velocity = Vector();
        Game::get().getECS().addComponent(player, pVelocity);

        MoveOnInputComponent pMoveOnInput;
        pMoveOnInput.down = SDL_SCANCODE_S;
        pMoveOnInput.up = SDL_SCANCODE_W;
        pMoveOnInput.left = SDL_SCANCODE_A;
        pMoveOnInput.right = SDL_SCANCODE_D;
        Game::get().getECS().addComponent(player, pMoveOnInput);

        RectColliderComponent pCollider;
        pCollider.bounds = Vector(50, 50);
        pCollider.isStatic = false;
        Game::get().getECS().addComponent<ColliderComponent>(player, pCollider);


    }

    void SecondaryScene::initializeEntities(){
        EntityID player = Game::get().getECS().createEntity();

        TransformComponent pTransform;
        pTransform.position.set(400, 300);
        pTransform.scale.set(100, 100);
        Game::get().getECS().addComponent(player, pTransform);

        TextureRendererComponent pTexRenderer;
        pTexRenderer.sprite = new Sprite("assets/sprites/player-sprite.png");
        Game::get().getECS().addComponent(player, pTexRenderer);

        VelocityComponent pVelocity;
        pVelocity.velocity.set(0, 0);
        Game::get().getECS().addComponent(player, pVelocity);

        MoveOnInputComponent pMoveOnInput;
        pMoveOnInput.down = SDL_SCANCODE_S;
        pMoveOnInput.up = SDL_SCANCODE_W;
        pMoveOnInput.left = SDL_SCANCODE_A;
        pMoveOnInput.right = SDL_SCANCODE_D;
        Game::get().getECS().addComponent(player, pMoveOnInput);


       
    }
}