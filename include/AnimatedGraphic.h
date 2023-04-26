#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

class AnimatedGraphic : public SDLGameObject{
    public:
        AnimatedGraphic();
        ~AnimatedGraphic();

        virtual void load(const LoaderParams* pParams, int animSpeed);

        virtual void draw();
        virtual void update();
        virtual void clean();

    private:
        int m_animSpeed;

        int m_numFrames = 2;
};

class AnimatedGraphicCreator : public BaseCreator {
    GameObject* createGameObject() const{
        return new AnimatedGraphic();
    }
};

#endif