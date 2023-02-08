#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams):
    SDLGameObject(pParams){
}
    
Player::~Player(){

}

void Player::draw(){
    SDLGameObject::draw();
}
void Player::update(){

    handleInput();
    
    m_currentFrame = int(SDL_GetTicks() / 100) % 4;

    SDLGameObject::update();
}
void Player::clean(){
    std::cout << "clean player" << std::endl;
}

void Player::handleInput(){
    if(TheInputHandler::Instance()->joysticksInitialised()){
        m_velocity.setX(1 * TheInputHandler::Instance()->xValue(0,1));
        m_velocity.setY(1 * TheInputHandler::Instance()->yValue(0,1));
    }
}