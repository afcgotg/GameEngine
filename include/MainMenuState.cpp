#include <iostream>
#include <cstring>

#include "MainMenuState.h"
#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "Callback.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        if(!TheGame::Instance()->getStateMachine()->getStateChanged()){
            m_gameObjects[i]->update();
        }else{
            TheGame::Instance()->getStateMachine()->setStateChanged(false);
            break;
        }
            
    }
}

void MainMenuState::render(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }
}

bool MainMenuState::onEnter(const char* filePath){
    std::cout << "OnEnter function MainMenuState" << std::endl;
    StateParser stateParser;

    char* fullPath;
    fullPath = (char*) calloc(strlen(filePath) + strlen("/test.xml") + 1, sizeof(char));
    strcpy(fullPath, filePath);
    strcat(fullPath, "/test.xml");
    
    if(!stateParser.parseState(fullPath, s_menuID,  &m_gameObjects, &m_textureIDList)){
        std::cout << "Error" << std::endl;     
    }
    
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    setCallbacks(m_callbacks);

    std::cout << "entering MainMenuState" << std::endl;

    return true;
}

bool MainMenuState::onExit(){
    for(int i = 0; i > m_textureIDList.size(); i++){
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    return true;
}

std::string MainMenuState::getStateID() const{
    return s_menuID;
}

void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks){
    for(int i = 0; i < m_gameObjects.size(); i++){
        if(dynamic_cast<MenuButton*>(m_gameObjects[i])){
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            std::cout << pButton->getCallbackID() << std::endl;
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }else{
            
        }
    }
}

void MainMenuState::s_menuToPlay(){
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu(){
    TheGame::Instance()->clean();
}