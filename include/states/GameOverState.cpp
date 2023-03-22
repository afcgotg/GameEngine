#include "GameOverState.h"
#include "MainMenuState.h"
#include "PlayState.h"

#include "../gears/TextureManager.h"
#include "../gears/LoaderParams.h"
#include "../game_objects/AnimatedGraphic.h"
#include "../game_objects/MenuButton.h"
#include "StateParser.h"

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
    StateParser stateParser;
    stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);

    std::cout << "entering gameOver State" << std::endl;
    
    return true;
}

bool GameOverState::onExit(){
        for(int i = 0; i < m_textureIDList.size(); i++){
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    return true;
}

std::string GameOverState::getStateID() const{
    return s_gameOverID;
}

void GameOverState::s_gameOverToMain(){
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay(){
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks){
    for(int i = 0; i < m_gameObjects.size(); i++){
        if(dynamic_cast<MenuButton*>(m_gameObjects[i])){
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}