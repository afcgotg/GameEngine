#include <iostream>

#include "PlayState.h"
#include "../gears/TextureManager.h"
#include "../gears/InputHandler.h"
#include "../entities/Player.h"
#include "../Game.h"
#include "PauseState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update(){

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)){
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }

    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->update();
    }
}

void PlayState::render(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }
}

bool PlayState::onEnter(){
    if(!TheTextureManager::Instance()->load("assets/img/GraveRobber/GraveRobber_idle.png", "player", TheGame::Instance()->getRenderer())){
        return false;
    }

    GameObject* player = new Player(new LoaderParams(100, 100, 48, 48, "player"));

    m_gameObjects.push_back(player);
    
    return true;
}

bool PlayState::onExit(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("player");

    return true;
}

std::string PlayState::getStateID() const{
    return s_playID;
}