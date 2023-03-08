#include <iostream>

#include "MenuState.h"
#include "PlayState.h"
#include "../Game.h"
#include "../gears//TextureManager.h"
#include "../game_objects/MenuButton.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        if(!TheGame::Instance()->getStateMachine()->getStateChanged()){
            m_gameObjects[i]->update();
        }else{
            TheGame::Instance()->getStateMachine()->setStateChanged(false);
            break;
        }
            
    }
}

void MenuState::render(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter(){
    if(!TheTextureManager::Instance()->load("assets/img/playbutton.png", "playbutton", TheGame::Instance()->getRenderer())){
        return false;
    }

    if(!TheTextureManager::Instance()->load("assets/img/exitbutton.png", "exitbutton", TheGame::Instance()->getRenderer())){
        return false;
    }

    GameObject* playbutton = new MenuButton(new LoaderParams(328, 240, 144, 48, "playbutton"), s_menuToPlay);
    GameObject* exitbutton = new MenuButton(new LoaderParams(328, 360, 144, 48, "exitbutton"), s_exitFromMenu);

    m_gameObjects.push_back(playbutton);
    m_gameObjects.push_back(exitbutton);

    return true;
}

bool MenuState::onExit(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("playbutton");
    TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

    TheGame::Instance()->getStateMachine()->setStateChanged(true);

    return true;
}

std::string MenuState::getStateID() const{
    return s_menuID;
}

void MenuState::s_menuToPlay(){
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu(){
    TheGame::Instance()->clean();
}