#include "SDLGameObject.h"
#include "../gears/LoaderParams.h"

#ifndef __Player__
#define __Player__

class Player : public SDLGameObject{
    public:
        Player();
        ~Player();

        void load(const LoaderParams* pParams);

        virtual void draw();
        virtual void update();
        virtual void clean();

    private:
        void handleInput();
};

class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};

#endif