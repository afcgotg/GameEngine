#include <string>
#include <cstdint>

#ifndef __LoaderParams__
#define __LoaderParams__

class LoaderParams{
    public:
        LoaderParams(int x, int y, int width, int height, std::string textureID, uint32_t numFrames = 0, uint64_t callbackID = 0, uint32_t animSpeed = 0);

        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        std::string getTextureID() const;
        uint32_t getNumFrames() const;
        uint64_t getCallbackID() const;
        uint32_t getAnimSpeed() const;

    private:
        int m_x;
        int m_y;

        int m_width;
        int m_height;

        std::string m_textureID;

        uint32_t m_numFrames;
        uint32_t m_animSpeed;

        uint64_t m_callbackID;
};

#endif