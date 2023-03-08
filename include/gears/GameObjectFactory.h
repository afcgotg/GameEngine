#include "../game_objects/GameObject.h"

#ifndef __GAMEOBJECTFACTORY__
#define __GAMEOBJECTFACTORY__

class GameObjectFactory{

public:
    GameObject* createGameObject(ID id);

private:


};

#endif