#include "GameObjectFactory.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"

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