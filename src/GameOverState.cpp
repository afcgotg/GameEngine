#include "TextureManager.h"
#include "LoaderParams.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "Game.h"
#include "FileManager.h"

#include "GameOverState.h"
#include "MainMenuState.h"
#include "PlayState.h"

const std::string GameOverState::mGameOverID = "GAMEOVER";

void GameOverState::update(){
    for(size_t i = 0; i < mGameObjects.size(); i++){
        if(!TheGameStateMachine::Instance()->getStateChanged()){
            mGameObjects[i]->update();
        }else{
            TheGameStateMachine::Instance()->setStateChanged(false);
            break;
        }    
    }
}

void GameOverState::render(){
    for(size_t i = 0; i < mGameObjects.size(); i++){
        mGameObjects[i]->draw();
    }
}

bool GameOverState::onEnter(){
    std::string filePath = TheFileManager::Instance()->GetStatesFilePath();

    StateParser stateParser;
    stateParser.parseState(mGameOverID, &mGameObjects, &mTextureIDList);

    mCallbacks.push_back(0);
    mCallbacks.push_back(s_gameOverToMain);
    mCallbacks.push_back(s_restartPlay);
    setCallbacks(mCallbacks);

    return true;
}

bool GameOverState::onExit(){
        for(size_t i = 0; i < mTextureIDList.size(); i++){
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);
    }
    return true;
}

std::string GameOverState::getStateID() const{
    return mGameOverID;
}

void GameOverState::s_gameOverToMain(){
    TheGameStateMachine::Instance()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay(){
    TheGameStateMachine::Instance()->changeState(new PlayState());
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks){
    for(size_t i = 0; i < mGameObjects.size(); i++){
        if(dynamic_cast<MenuButton*>(mGameObjects[i])){
            MenuButton* pButton = dynamic_cast<MenuButton*>(mGameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}