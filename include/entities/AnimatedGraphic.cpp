#include <SDL2/SDL.h>
#include <iostream>

#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int animSpeed) : SDLGameObject(pParams), m_animSpeed(animSpeed){

}

AnimatedGraphic::~AnimatedGraphic(){}

void AnimatedGraphic::draw(){
    SDLGameObject::draw();
}

void AnimatedGraphic::update(){
    m_currentFrame = int(SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames;
}

void AnimatedGraphic::clean(){
}