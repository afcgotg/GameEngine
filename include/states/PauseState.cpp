#include "PauseState.h"
#include "../Game.h"
#include "MenuState.h"
#include "../gears/TextureManager.h"
#include "../gears/InputHandler.h"
#include "../entities/MenuButton.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain(){
    TheGame::Instance()->getStateMachine()->changeState(new MenuState());
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
    if(!TheTextureManager::Instance()->load("assets/img/resumebutton.png", "resumebutton", TheGame::Instance()->getRenderer())){
        return false;
    }
    if(!TheTextureManager::Instance()->load("assets/img/mainmenubutton.png", "mainmenubutton", TheGame::Instance()->getRenderer())){
        return false;
    }

    GameObject* mainbutton = new MenuButton(new LoaderParams(328, 300, 144, 48, "mainmenubutton"), s_pauseToMain);
    GameObject* resumebutton = new MenuButton(new LoaderParams(328, 372, 144, 48, "resumebutton"), s_resumePlay);

    m_gameObjects.push_back(mainbutton);
    m_gameObjects.push_back(resumebutton);
    
    return true;
}

bool PauseState::onExit(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
    TheTextureManager::Instance()->clearFromTextureMap("mainmenubutton");

    TheInputHandler::Instance()->reset();

    TheGame::Instance()->getStateMachine()->setStateChanged(true);

    return true;
}

std::string PauseState::getStateID() const{
    return s_pauseID;
}