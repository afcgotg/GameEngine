#include "GameObjectFactory.h"
#include "../game_objects/Player.h"
#include "../game_objects/Enemy.h"

GameObject* GameObjectFactory::createGameObject(ID id){
    switch(id){
        case "PLAYER":
            return new Player();
            break;
        case "ENEMY":
            return new Enemy();
            break;
        default:
            return NULL;
    }
}