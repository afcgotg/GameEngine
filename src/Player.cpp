#include "Player.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"

Player::Player(): SDLGameObject()
{
}
    
Player::~Player()
{
}

void Player::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
}

void Player::draw(){
    SDLGameObject::draw();
}
void Player::update(){

    handleInput();
    
    mCurrentFrame = (SDL_GetTicks() / 100) % 1;

    SDLGameObject::update();
}
void Player::clean(){
    std::cout << "clean player" << std::endl;
}

void Player::handleInput(){
    // if(TheInputHandler::Instance()->joysticksInitialised()){
    //     mVelocity.setX(1 * TheInputHandler::Instance()->dpad_xValue(0));
    //     mVelocity.setY(1 * TheInputHandler::Instance()->dpad_yValue(0));
    // }
    
    
    // if(TheInputHandler::Instance()->getMouseButtonState(LEFT)){
    //     mVelocity.setX(1);
    // }else{
    //     mVelocity.setX(0);
    // }

    // Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
    // mVelocity = (*vec - mPosition) / 100;

    // https://wiki.libsdl.org/SDL2/SDL_Keycode

    // if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)){
    //     mVelocity.setX(2);
    // }else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)){
    //     mVelocity.setX(-2);
    // }else{
    //     mVelocity.setX(0);
    // }

    // if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)){
    //     mVelocity.setY(-2);
    // }else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)){
    //     mVelocity.setY(2);
    // }else{
    //      mVelocity.setY(0);
    // }

    Vector2D* target = TheInputHandler::Instance()->getMousePosition();

    mVelocity = *target - mPosition;
    mVelocity /= 50;

}