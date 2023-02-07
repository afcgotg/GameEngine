#include "SDLGameObject.h"
#include "LoaderParams.h"

#ifndef __Enemy__
#define __Enemy__

class Enemy : public SDLGameObject{
    public:
        Enemy(const LoaderParams* pParams);
        ~Enemy();

        virtual void draw();
        virtual void update();
        virtual void clean();
};

#endif