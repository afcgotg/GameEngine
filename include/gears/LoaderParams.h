#include <string>

#ifndef __LoaderParams__
#define __LoaderParams__

class LoaderParams{
    public:
        LoaderParams(int x, int y, int width, int height, int textureID, int numFrames = 0, int callbackID = 0, int animSpeed = 0);

        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        int getTextureID() const;
        int getNumFrames() const;
        int getCallbackID() const;
        int getAnimSpeed() const;

    private:
        int m_x;
        int m_y;

        int m_width;
        int m_height;

        int m_textureID;

        int m_numFrames;
        int m_animSpeed;

        int m_callbackID;
};

#endif