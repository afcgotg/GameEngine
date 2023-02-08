#include "SDLGameObject.h"
#include "LoaderParams.h"

#ifndef __Player__
#define __Player__

class Player : public SDLGameObject{
    public:
        Player(const LoaderParams* pParams);
        ~Player();

        virtual void draw();
        virtual void update();
        virtual void clean();

    private:
        void handleInput();
};

#endif