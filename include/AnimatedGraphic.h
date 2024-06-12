#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

class AnimatedGraphic : public SDLGameObject{
    public:
        AnimatedGraphic();
        ~AnimatedGraphic();

        virtual void load(const LoaderParams* pParams);

        virtual void draw();
        virtual void update();
        virtual void clean();

    private:
        uint32_t mAnimSpeed;
        uint32_t mNumFrames = 1;
};

class AnimatedGraphicCreator : public BaseCreator {
    GameObject* createGameObject() const{
        return new AnimatedGraphic();
    }
};

#endif