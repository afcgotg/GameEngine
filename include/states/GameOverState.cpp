#include "GameOverState.h"
#include "MenuState.h"
#include "PlayState.h"

#include "../gears/TextureManager.h"
#include "../gears/LoaderParams.h"
#include "../entities/AnimatedGraphic.h"
#include "../entities/MenuButton.h"

#include "../Game.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        if(!TheGame::Instance()->getStateMachine()->getStateChanged()){
            m_gameObjects[i]->update();
        }else{
            TheGame::Instance()->getStateMachine()->setStateChanged(false);
            break;
        }    
    }
}

void GameOverState::render(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }
}

bool GameOverState::onEnter(){
    if(!TheTextureManager::Instance()->load("assets/img/gameover.png", "gameovertext", TheGame::Instance()->getRenderer())){
        return false;
    }
    if(!TheTextureManager::Instance()->load("assets/img/mainmenubutton.png", "mainmenubutton", TheGame::Instance()->getRenderer())){
        return false;
    }
    if(!TheTextureManager::Instance()->load("assets/img/restartbutton.png", "restartbutton", TheGame::Instance()->getRenderer())){
        return false;
    }

    GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(292, 228, 216, 48, "gameovertext", 2), 2);
    GameObject* menubutton = new MenuButton(new LoaderParams(328, 300, 144, 48, "mainmenubutton"), s_gameOverToMain);
    GameObject* restartbutton = new MenuButton(new LoaderParams(328, 372, 144, 48, "restartbutton"), s_restartPlay);

    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(menubutton);
    m_gameObjects.push_back(restartbutton);

    return true;

    
}
bool GameOverState::onExit(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("gameovertext");
    TheTextureManager::Instance()->clearFromTextureMap("mainmenubutton");
    TheTextureManager::Instance()->clearFromTextureMap("restartbutton");

    TheGame::Instance()->getStateMachine()->setStateChanged(true);

    return true;
}

std::string GameOverState::getStateID() const{
    return s_gameOverID;
}

void GameOverState::s_gameOverToMain(){
    TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay(){
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}