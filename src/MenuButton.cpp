#include <iostream>

#include "InputHandler.h"
#include "MenuButton.h"

MenuButton::MenuButton() : SDLGameObject(){
}

MenuButton::~MenuButton(){
}

void MenuButton::load(const LoaderParams* pParams){
    SDLGameObject::load(pParams);
    mCallbackID = pParams->getCallbackID();
    mCurrentFrame = MOUSE_OUT;
    mPressed = false;
}

void MenuButton::setCallback(void(*callback)()){
    mCallback = callback;
}

uint64_t MenuButton::getCallbackID(){
    return mCallbackID;
}


void MenuButton::draw(){
    SDLGameObject::draw();
}

void MenuButton::update(){
    Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

    if(pMousePos->getX() < (mPosition.getX() + mWidth) &&
    pMousePos->getX() > mPosition.getX() &&
    pMousePos->getY() < (mPosition.getY() + mHeight) &&
    pMousePos->getY() > mPosition.getY()){

        mCurrentFrame = MOUSE_OVER;
        if(TheInputHandler::Instance()->getMouseButtonState(LEFT)){
            mCurrentFrame = CLICKED;
            mPressed = true;
        }else if(!TheInputHandler::Instance()->getMouseButtonState(LEFT) && mPressed){
            mCallback();
            mPressed = false;
        }
    }else{
        mCurrentFrame = MOUSE_OUT;
        mPressed = false;
    }
}

void MenuButton::clean(){
    SDLGameObject::clean();
}