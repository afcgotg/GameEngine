#include "Enemy.h"

Enemy::Enemy(const LoaderParams* pParams):
    SDLGameObject(pParams){
}
    
Enemy::~Enemy(){

}

void Enemy::draw(){
    SDLGameObject::draw();
}

void Enemy::update(){
    m_y += 1;
    m_currentFrame = int(SDL_GetTicks() / 100) % 4;
}

void Enemy::clean(){
    std::cout << "clean player" << std::endl;
}