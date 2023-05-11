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

        Vector2D m_position;
        Vector2D m_velocity;
        Vector2D m_acceleration;

        int m_width;
        int m_height;
        uint32_t m_currentRow;
        uint32_t m_currentFrame;
        uint32_t m_numFrames;
        uint64_t m_callbackID;

        std::string m_textureID;
};

#endif
