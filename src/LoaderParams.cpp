#include "LoaderParams.h"

LoaderParams::LoaderParams(int x, int y, int width, int height, std::string textureID, uint32_t numFrames, uint64_t callbackID, uint32_t animSpeed):
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height),
    m_textureID(textureID),
    m_numFrames(numFrames),
    m_animSpeed(animSpeed),
    m_callbackID(callbackID)
{
}

int LoaderParams::getX() const{
    return m_x;
}

int LoaderParams::getY() const{
    return m_y;
}

int LoaderParams::getWidth() const{
    return m_width;
}

int LoaderParams::getHeight() const{
    return m_height;
}

std::string LoaderParams::getTextureID() const{
    return m_textureID;
}

uint32_t LoaderParams::getNumFrames() const{
    return m_numFrames;
}

uint64_t LoaderParams::getCallbackID() const{
    return m_callbackID;
}

uint32_t LoaderParams::getAnimSpeed() const{
    return m_animSpeed;
}