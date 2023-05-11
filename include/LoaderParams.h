#include <string>

#ifndef __LoaderParams__
#define __LoaderParams__

class LoaderParams{
    public:
        LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID, int animSpeed);

        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        std::string getTextureID() const;
        int getNumFrames() const;
        int getCallbackID() const;
        uint32_t getAnimSpeed() const;

    private:
        int m_x;
        int m_y;

        int m_width;
        int m_height;

        std::string m_textureID;

        int m_numFrames;
        uint32_t m_animSpeed;

        int m_callbackID;
};

#endif