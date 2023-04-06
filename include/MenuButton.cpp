#include <iostream>

#include "InputHandler.h"
#include "MenuButton.h"

MenuButton::MenuButton() : SDLGameObject(){
}

MenuButton::~MenuButton(){
}

void MenuButton::load(const LoaderParams* pParams){
    SDLGameObject::load(pParams);
    m_callbackID = pParams->getCallbackID();
    m_currentFrame = MOUSE_OUT;
    m_bPressed = false;
}

void MenuButton::setCallback(void(*callback)()){
    m_callback = callback;
}

int MenuButton::getCallbackID(){
    return m_callbackID;
}


void MenuButton::draw(){
    SDLGameObject::draw();
}

void MenuButton::update(){
    Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

    if(pMousePos->getX() < (m_position.getX() + m_width) &&
    pMousePos->getX() > m_position.getX() &&
    pMousePos->getY() < (m_position.getY() + m_height) &&
    pMousePos->getY() > m_position.getY()){

        m_currentFrame = MOUSE_OVER;
        if(TheInputHandler::Instance()->getMouseButtonState(LEFT)){
            m_currentFrame = CLICKED;
            m_bPressed = true;
        }else if(!TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bPressed){
            m_callback();
            m_bPressed = false;
        }
    }else{
        m_currentFrame = MOUSE_OUT;
        m_bPressed = false;
    }
}

void MenuButton::clean(){
    SDLGameObject::clean();
}