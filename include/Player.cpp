#include "Player.h"

Player::Player(const LoaderParams* pParams):
    SDLGameObject(pParams){
}
    
Player::~Player(){

}

void Player::draw(){
    SDLGameObject::draw();
}
void Player::update(){
    m_acceleration.setX(1);
    SDLGameObject::update();
    m_currentFrame = int(SDL_GetTicks() / 100) % 4;
}
void Player::clean(){
    std::cout << "clean player" << std::endl;
}