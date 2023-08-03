#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "StateParser.h"
#include <cstring>


const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain(){
    TheGameStateMachine::Instance()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay(){
    TheGameStateMachine::Instance()->popState();
}

void PauseState::update(){
    for(uint64_t i = 0; i < m_gameObjects.size(); i++){
        if(!TheGameStateMachine::Instance()->getStateChanged()){
            m_gameObjects[i]->update();
        }else{
            TheGameStateMachine::Instance()->setStateChanged(false);
            break;
        }
    }
}

void PauseState::render(){
    for(uint64_t i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }
}

bool PauseState::onEnter(std::string filePath){
    StateParser stateParser;

    std::string fullPath(filePath);
    fullPath += "\\states.xml";

    stateParser.parseState(fullPath, s_pauseID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);

    setCallbacks(m_callbacks);

    std::cout << "entering PauseState" << std::endl;

    return true;
}

bool PauseState::onExit(){
    for(uint64_t i = 0; i < m_textureIDList.size(); i++){
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    return true;
}

std::string PauseState::getStateID() const{
    return s_pauseID;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks){
    for(uint64_t i = 0; i < m_gameObjects.size(); i++){
        if(dynamic_cast<MenuButton*>(m_gameObjects[i])){
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}