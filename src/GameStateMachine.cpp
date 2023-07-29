#include "GameStateMachine.h"
#include "Game.h"

#include <iostream>
#include <cstring>

GameStateMachine* GameStateMachine::_instance = nullptr;
std::vector<GameState*> GameStateMachine::m_gameStates;

GameStateMachine* GameStateMachine::Instance()
{
    if(_instance == nullptr)
        _instance = new GameStateMachine();
    return _instance;
}

void GameStateMachine::pushState(GameState* pState){
    m_gameStates.push_back(pState);
    char* assetsPath = static_cast<char*>(calloc(strlen(TheGame::Instance()->GetExecutionPath()) + strlen("/assets") + 1, sizeof(char)));
    strcpy(assetsPath, TheGame::Instance()->GetExecutionPath());
    strcat(assetsPath, "/assets");
    m_gameStates.back()->onEnter(assetsPath);
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
            //delete m_gameStates.back();
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

bool GameStateMachine::getStateChanged(){return m_bStateChanged;}