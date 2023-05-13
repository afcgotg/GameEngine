#include "GameStateMachine.h"

#include <iostream>
#include <cstring>

GameStateMachine::~GameStateMachine(){}

void GameStateMachine::pushState(GameState* pState){
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter(m_path);
}

void GameStateMachine::changeState(GameState* pState){
    if(!m_gameStates.empty()){
        if(m_gameStates.back()->getStateID() == pState->getStateID()){
            return; // do nothing
        }
        GameStateMachine::popState();
    }
    GameStateMachine::pushState(pState);
}

void GameStateMachine::popState(){
    if(!m_gameStates.empty()){
        if(m_gameStates.back()->onExit()){
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}

void GameStateMachine::update(){
    if(!m_gameStates.empty()){
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render(){
    if(!m_gameStates.empty()){
        m_gameStates.back()->render();
    }
}

void GameStateMachine::setStateChanged(bool change){
    m_bStateChanged = change;
}

void GameStateMachine::setPath(const char* path){
    m_path = static_cast<char*>(calloc(strlen(path) + strlen("/assets") + 1, sizeof(char)));
    strcpy(m_path, path);
    strcat(m_path, "/assets");
    
}

bool GameStateMachine::getStateChanged(){return m_bStateChanged;}