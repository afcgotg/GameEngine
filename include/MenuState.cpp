#include <iostream>

#include "MenuState.h"
#include "Game.h"
#include "TextureManager.h"
#include "MenuButton.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->update();
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

    // if(!TheTextureManager::Instance()->load("assets/exitbutton.png", "exitbutton", TheGame::Instance()->getRenderer())){
    //     return false;
    // }

    GameObject* playbutton = new MenuButton(new LoaderParams(100, 100, 144, 48, "playbutton"));
    // GameObject* exitbutton = new MenuButton(new LoaderParams(100, 100, 144, 48, "exitbutton"));

    m_gameObjects.push_back(playbutton);
    // m_gameObjects.push_back(exitbutton);

    return true;
}

bool MenuState::onExit(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("playbutton");
    // TheTextureManager::Instance()->clearFromTextureMap("exitbutton");
    return true;
}

std::string MenuState::getStateID() const{
    return s_menuID;
}