#include "LoaderParams.h"

LoaderParams::LoaderParams(int x, int y, int width, int height, int textureID, int numFrames = 0, int callbackID = 0, int animSpeed = 0):
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height),
    m_textureID(textureID),
    m_numFrames(numFrames),
    m_callbackID(callbackID),
    m_animSpeed(animSpeed)
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

int LoaderParams::getTextureID() const{
    return m_textureID;
}

int LoaderParams::getNumFrames() const{
    return m_numFrames;
}

int LoaderParams::getCallbackID() const{
    return m_callbackID;
}

int LoaderParams::getAnimSpeed() const{
    return m_animSpeed;
}