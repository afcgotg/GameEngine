#include "SDLGameObject.h"
#include "../gears/LoaderParams.h"

#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

class AnimatedGraphic : public SDLGameObject{
    public:
        AnimatedGraphic(const LoaderParams* pParams, int animSpeed);
        ~AnimatedGraphic();

        virtual void draw();
        virtual void update();
        virtual void clean();

    private:
        int m_animSpeed;

        int m_numFrames = 2;
};

#endif