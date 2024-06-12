#include <../SDL2/include/SDL2/SDL.h>
#include <iostream>

#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : SDLGameObject(){

}

AnimatedGraphic::~AnimatedGraphic(){}


void AnimatedGraphic::load(const LoaderParams* pParams){
    SDLGameObject::load(pParams);
    mAnimSpeed = pParams->getAnimSpeed();
    mNumFrames = pParams->getNumFrames();
}

void AnimatedGraphic::draw(){
    SDLGameObject::draw();
}

void AnimatedGraphic::update(){
    mCurrentFrame = (SDL_GetTicks() / (1000 / mAnimSpeed)) % mNumFrames;
}

void AnimatedGraphic::clean(){
}