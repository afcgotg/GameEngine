#include "Player.h"
#include "../gears/InputHandler.h"
#include "../gears/TextureManager.h"
#include "../Game.h"

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
    // if(TheInputHandler::Instance()->joysticksInitialised()){
    //     m_velocity.setX(1 * TheInputHandler::Instance()->dpad_xValue(0));
    //     m_velocity.setY(1 * TheInputHandler::Instance()->dpad_yValue(0));
    // }
    
    
    // if(TheInputHandler::Instance()->getMouseButtonState(LEFT)){
    //     m_velocity.setX(1);
    // }else{
    //     m_velocity.setX(0);
    // }

    // Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
    // m_velocity = (*vec - m_position) / 100;

    // https://wiki.libsdl.org/SDL2/SDL_Keycode

    // if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)){
    //     m_velocity.setX(2);
    // }else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)){
    //     m_velocity.setX(-2);
    // }else{
    //     m_velocity.setX(0);
    // }

    // if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)){
    //     m_velocity.setY(-2);
    // }else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)){
    //     m_velocity.setY(2);
    // }else{
    //      m_velocity.setY(0);
    // }

    Vector2D* target = TheInputHandler::Instance()->getMousePosition();

    m_velocity = *target - m_position;
    m_velocity /= 50;

}