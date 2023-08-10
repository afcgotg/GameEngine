#include "LoaderParams.h"

LoaderParams::LoaderParams(int x, int y, int width, int height, std::string textureID, uint32_t numFrames, uint64_t callbackID, uint32_t animSpeed):
    mX(x),
    mY(y),
    mWidth(width),
    mHeight(height),
    mTextureID(textureID),
    mNumFrames(numFrames),
    mAnimSpeed(animSpeed),
    mCallbackID(callbackID)
{
}

int LoaderParams::getX() const{
    return mX;
}

int LoaderParams::getY() const{
    return mY;
}

int LoaderParams::getWidth() const{
    return mWidth;
}

int LoaderParams::getHeight() const{
    return mHeight;
}

std::string LoaderParams::getTextureID() const{
    return mTextureID;
}

uint32_t LoaderParams::getNumFrames() const{
    return mNumFrames;
}

uint64_t LoaderParams::getCallbackID() const{
    return mCallbackID;
}

uint32_t LoaderParams::getAnimSpeed() const{
    return mAnimSpeed;
}