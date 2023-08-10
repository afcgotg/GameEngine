#include <../SDL2/include/SDL2/SDL.h>
#include <iostream>

#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : SDLGameObject(){

}

AnimatedGraphic::~AnimatedGraphic(){}


void AnimatedGraphic::load(const LoaderParams* pParams){
    SDLGameObject::load(pParams);
    m_animSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::draw(){
    SDLGameObject::draw();
}

void AnimatedGraphic::update(){
    m_currentFrame = (SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames;
}

void AnimatedGraphic::clean(){
}