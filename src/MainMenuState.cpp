#include <iostream>
#include <cstring>

#include "MainMenuState.h"
#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "Callback.h"
#include "FileManager.h"

const std::string MainMenuState::mMenuID = "MENU";

void MainMenuState::update(){
    for(size_t i = 0; i < mGameObjects.size(); i++){
        if(!TheGameStateMachine::Instance()->getStateChanged()){
            mGameObjects[i]->update();
        }else{
            TheGameStateMachine::Instance()->setStateChanged(false);
            break;
        }
            
    }
}

void MainMenuState::render(){
    for(size_t i = 0; i < mGameObjects.size(); i++){
        mGameObjects[i]->draw();
    }
}

bool MainMenuState::onEnter(){
    
    std::string filepath = TheFileManager::Instance()->GetStatesFilePath();

    StateParser stateParser;
    stateParser.parseState(mMenuID, &mGameObjects, &mTextureIDList);    
        
    mCallbacks.push_back(0);
    mCallbacks.push_back(mMenuToPlay);
    mCallbacks.push_back(mExitFromMenu);
    setCallbacks(mCallbacks);

    return true;
}

bool MainMenuState::onExit(){
    for(size_t i = 0; i > mTextureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);
    }
    return true;
}

std::string MainMenuState::getStateID() const{
    return mMenuID;
}

void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks){
    for(size_t i = 0; i < mGameObjects.size(); i++){
        if(dynamic_cast<MenuButton*>(mGameObjects[i])){
            MenuButton* pButton = dynamic_cast<MenuButton*>(mGameObjects[i]);
            std::cout << pButton->getCallbackID() << std::endl;
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }else{
            
        }
    }
}

void MainMenuState::mMenuToPlay(){
    TheGameStateMachine::Instance()->changeState(new PlayState());
}

void MainMenuState::mExitFromMenu(){
    TheGame::Instance()->Clean();
}