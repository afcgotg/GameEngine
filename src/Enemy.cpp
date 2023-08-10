#include <../SDL2/include/SDL2/SDL.h>

#include "Enemy.h"

Enemy::Enemy(): SDLGameObject(){
}
    
Enemy::~Enemy(){

}

void Enemy::load(const LoaderParams* pParams){
    SDLGameObject::load(pParams);
    mVelocity.setY(2);
}

void Enemy::draw(){
    SDLGameObject::draw();
}

void Enemy::update(){
    mCurrentFrame = (SDL_GetTicks() / 60) % 6;

    if(mPosition.getY() < 0){
        mVelocity.setY(2);
    }else if(mPosition.getY() > 600 - 48){
        mVelocity.setY(-2);
    }

    SDLGameObject::update();
}

void Enemy::clean(){
}