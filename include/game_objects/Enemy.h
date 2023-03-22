#include "SDLGameObject.h"
#include "../gears/LoaderParams.h"

#ifndef __Enemy__
#define __Enemy__

class Enemy : public SDLGameObject{
    public:
        Enemy();
        ~Enemy();

        virtual void load(const LoaderParams* pParams);

        virtual void draw();
        virtual void update();
        virtual void clean();
};

class EnemyCreator : public BaseCreator
{
    GameObject* createGameObject() const{
        return new Enemy();
    }
};

#endif