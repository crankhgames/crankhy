#include "scene/scene.h"
#include "game.h"



namespace Crankhy{

    void spawnBlock(){

        EntityID block = Game::get().getECSManager().createEntity();

        float randomRadius = rand() / (float)RAND_MAX * 45 + 15;
        float randomX = rand() / (float)RAND_MAX * 700 + 50;
        float randomY = rand() / (float)RAND_MAX * 500 + 50;

        TransformComponent bTransform;
        bTransform.position = Vector(randomX, randomY);
        bTransform.scale = Vector(randomRadius*2, randomRadius*2);
        Game::get().getECSManager().addComponent(block, bTransform);

        TextureRendererComponent bTextRenderer;
        bTextRenderer.sprite = new Sprite("assets/sprites/player-sprite.png");
        Game::get().getECSManager().addComponent(block, bTextRenderer);

        VelocityComponent bVelocity;
        bVelocity.velocity = Vector();
        Game::get().getECSManager().addComponent(block, bVelocity);

        RectColliderComponent bCollider;
        bCollider.bounds = {randomRadius*2, randomRadius*2};
        bCollider.isStatic = true;
        Game::get().getECSManager().addComponent<ColliderComponent>(block, bCollider);
    }

    void MainScene::initializeEntities() {
        for (int i = 0; i < 250; i++){
            spawnBlock();
        }

        EntityID player = Game::get().getECSManager().createEntity();

        TransformComponent pTransform;
        pTransform.position = Vector(400, 300);
        pTransform.scale = Vector(50, 50);
        Game::get().getECSManager().addComponent(player, pTransform);

        TextureRendererComponent pTexRenderer;
        pTexRenderer.sprite = new Sprite("assets/sprites/logo.png");
        Game::get().getECSManager().addComponent(player, pTexRenderer);

        VelocityComponent pVelocity;
        pVelocity.velocity = Vector();
        Game::get().getECSManager().addComponent(player, pVelocity);

        MoveOnInputComponent pMoveOnInput;
        pMoveOnInput.down = SDL_SCANCODE_S;
        pMoveOnInput.up = SDL_SCANCODE_W;
        pMoveOnInput.left = SDL_SCANCODE_A;
        pMoveOnInput.right = SDL_SCANCODE_D;
        Game::get().getECSManager().addComponent(player, pMoveOnInput);

        RectColliderComponent pCollider;
        pCollider.bounds = Vector(50, 50);
        pCollider.isStatic = false;
        Game::get().getECSManager().addComponent<ColliderComponent>(player, pCollider);


    }

    void SecondaryScene::initializeEntities(){
        EntityID player = Game::get().getECSManager().createEntity();

        TransformComponent pTransform;
        pTransform.position.set(400, 300);
        pTransform.scale.set(100, 100);
        Game::get().getECSManager().addComponent(player, pTransform);

        TextureRendererComponent pTexRenderer;
        pTexRenderer.sprite = new Sprite("assets/sprites/player-sprite.png");
        Game::get().getECSManager().addComponent(player, pTexRenderer);

        VelocityComponent pVelocity;
        pVelocity.velocity.set(0, 0);
        Game::get().getECSManager().addComponent(player, pVelocity);

        MoveOnInputComponent pMoveOnInput;
        pMoveOnInput.down = SDL_SCANCODE_S;
        pMoveOnInput.up = SDL_SCANCODE_W;
        pMoveOnInput.left = SDL_SCANCODE_A;
        pMoveOnInput.right = SDL_SCANCODE_D;
        Game::get().getECSManager().addComponent(player, pMoveOnInput);


       
    }
}