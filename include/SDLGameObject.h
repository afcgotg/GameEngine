#include <string>

#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

#ifndef __SDLGameObject__
#define __SDLGameObject__

class SDLGameObject : public GameObject{
    public:
        SDLGameObject ();

        void load(const LoaderParams* pParams);

        virtual void draw();
        virtual void update();
        virtual void clean();

        virtual Vector2D& getPosition();
        virtual int getWidth();
        virtual int getHeight();

    protected:

        Vector2D mPosition;
        Vector2D mVelocity;
        Vector2D mAcceleration;

        int mWidth;
        int mHeight;
        uint32_t mCurrentRow;
        uint32_t mCurrentFrame;
        uint32_t mNumFrames;
        uint64_t mCallbackID;

        std::string mTextureID;
};

#endif
