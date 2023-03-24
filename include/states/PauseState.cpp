#include "PauseState.h"
#include "../Game.h"
#include "MainMenuState.h"
#include "../gears/TextureManager.h"
#include "../gears/InputHandler.h"
#include "../game_objects/MenuButton.h"
#include "StateParser.h"


const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain(){
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay(){
    TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        if(!TheGame::Instance()->getStateMachine()->getStateChanged()){
            m_gameObjects[i]->update();
        }else{
            TheGame::Instance()->getStateMachine()->setStateChanged(false);
            break;
        }
    }
}

void PauseState::render(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }
}

bool PauseState::onEnter(){
    StateParser stateParser;
    stateParser.parseState("test.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);

    setCallbacks(m_callbacks);

    std::cout << "entering PauseState" << std::endl;

    return true;
}

bool PauseState::onExit(){
    for(int i = 0; i < m_textureIDList.size(); i++){
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    return true;
}

std::string PauseState::getStateID() const{
    return s_pauseID;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks){
    for(int i = 0; i < m_gameObjects.size(); i++){
        if(dynamic_cast<MenuButton*>(m_gameObjects[i])){
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}