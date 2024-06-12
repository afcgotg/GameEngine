#include "SDLGameObject.h"

#include "Game.h"
#include "TextureManager.h"

SDLGameObject::SDLGameObject() : GameObject(){
}

void SDLGameObject::load(const LoaderParams* pParams)
{
    mPosition = Vector2D(pParams->getX(), pParams->getY());
    mVelocity = Vector2D(0,0);
    mAcceleration = Vector2D(0,0);
    mWidth = pParams->getWidth();
    mHeight = pParams->getHeight();
    mTextureID = pParams->getTextureID();
    mCurrentRow = 1;
    mCurrentFrame = 1;
    mNumFrames = pParams->getNumFrames();
}

void SDLGameObject::draw(){
    TheTextureManager::Instance()->drawFrame(mTextureID, static_cast<int>(mPosition.getX()), static_cast<int>(mPosition.getY()), mWidth, mHeight, mCurrentRow, mCurrentFrame, TheGameWindow::Instance()->GetRenderer());
}

void SDLGameObject::update(){
    mPosition += mVelocity;
    mVelocity += mAcceleration;
}

void SDLGameObject::clean(){}

Vector2D& SDLGameObject::getPosition(){
    return mPosition;
}

int SDLGameObject::getWidth(){
    return mWidth;
}

int SDLGameObject::getHeight(){
    return mHeight;
}