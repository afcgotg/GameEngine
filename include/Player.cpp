#include "Player.h"

Player::Player(){

}
    
Player::~Player(){

}

void Player::draw(){
    GameObject::draw();
    std::cout << "draw player" << std::endl;
}
void Player::update(){
    std::cout << "update player" << std::endl;
    m_x = 10;
    m_y = 20;
}
void Player::clean(){
    GameObject::clean();
    std::cout << "clean player" << std::endl;
}