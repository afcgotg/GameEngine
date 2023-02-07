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
    m_x -= 1;
}
void Player::clean(){
    std::cout << "clean player" << std::endl;
}