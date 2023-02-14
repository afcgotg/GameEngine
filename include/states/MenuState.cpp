#include <iostream>

#include "MenuState.h"
#include "PlayState.h"
#include "../Game.h"
#include "../gears//TextureManager.h"
#include "../entities/MenuButton.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        if(!m_bComingOut){
            m_gameObjects[i]->update();
        }else{
            break;
        }
    }
}

void MenuState::render(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        if(!m_bComingOut){
            m_gameObjects[i]->draw();
        }else{
            break;
        }
    }
}

bool MenuState::onEnter(){
    if(!TheTextureManager::Instance()->load("assets/img/playbutton.png", "playbutton", TheGame::Instance()->getRenderer())){
        return false;
    }

    if(!TheTextureManager::Instance()->load("assets/img/exitbutton.png", "exitbutton", TheGame::Instance()->getRenderer())){
        return false;
    }

    GameObject* playbutton = new MenuButton(new LoaderParams(100, 100, 144, 48, "playbutton"), s_menuToPlay);
    GameObject* exitbutton = new MenuButton(new LoaderParams(100, 160, 144, 48, "exitbutton"), s_exitFromMenu);

    m_gameObjects.push_back(playbutton);
    m_gameObjects.push_back(exitbutton);

    m_bComingOut = false;

    return true;
}

bool MenuState::onExit(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("playbutton");
    TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

    m_bComingOut = true;

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