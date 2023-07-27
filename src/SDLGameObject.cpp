#include "SDLGameObject.h"

#include "Game.h"
#include "TextureManager.h"

SDLGameObject::SDLGameObject() : GameObject(){
}

void SDLGameObject::load(const LoaderParams* pParams)
{
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_velocity = Vector2D(0,0);
    m_acceleration = Vector2D(0,0);
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_currentRow = 1;
    m_currentFrame = 1;
    m_numFrames = pParams->getNumFrames();
}

void SDLGameObject::draw(){
    TheTextureManager::Instance()->drawFrame(m_textureID, static_cast<int>(m_position.getX()), static_cast<int>(m_position.getY()), m_width, m_height, m_currentRow, m_currentFrame, TheGameWindow::Instance()->GetRenderer());
}

void SDLGameObject::update(){
    m_position += m_velocity;
    m_velocity += m_acceleration;
}

void SDLGameObject::clean(){}

Vector2D& SDLGameObject::getPosition(){
    return m_position;
}

int SDLGameObject::getWidth(){
    return m_width;
}

int SDLGameObject::getHeight(){
    return m_height;
}