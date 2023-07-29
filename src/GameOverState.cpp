#include "TextureManager.h"
#include "LoaderParams.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "Game.h"

#include "GameOverState.h"
#include "MainMenuState.h"
#include "PlayState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update(){
    for(size_t i = 0; i < m_gameObjects.size(); i++){
        if(!TheGameStateMachine::Instance()->getStateChanged()){
            m_gameObjects[i]->update();
        }else{
            TheGameStateMachine::Instance()->setStateChanged(false);
            break;
        }    
    }
}

void GameOverState::render(){
    for(size_t i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }
}

bool GameOverState::onEnter(const char* filePath){
    StateParser stateParser;

    char* fullPath;
    fullPath = static_cast<char*>(calloc(strlen(filePath) + strlen("/states.xml") + 1, sizeof(char)));
    strcpy(fullPath, filePath);
    strcat(fullPath, "/states.xml");

    stateParser.parseState(fullPath, s_gameOverID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);

    std::cout << "entering gameOver State" << std::endl;
    
    return true;
}

bool GameOverState::onExit(){
        for(size_t i = 0; i < m_textureIDList.size(); i++){
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    return true;
}

std::string GameOverState::getStateID() const{
    return s_gameOverID;
}

void GameOverState::s_gameOverToMain(){
    TheGameStateMachine::Instance()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay(){
    TheGameStateMachine::Instance()->changeState(new PlayState());
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks){
    for(size_t i = 0; i < m_gameObjects.size(); i++){
        if(dynamic_cast<MenuButton*>(m_gameObjects[i])){
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}