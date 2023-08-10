#include <iostream>
#include <cstring>

#include "MainMenuState.h"
#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "Callback.h"

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

bool MainMenuState::onEnter(std::string filePath){
    std::cout << "OnEnter function MainMenuState" << std::endl;
    StateParser stateParser;

    std::string fullPath(filePath);

    fullPath += "\\states.xml";

    if (!stateParser.parseState(fullPath, mMenuID, &mGameObjects, &mTextureIDList))
        std::cout << "Error" << std::endl;
    
        
    mCallbacks.push_back(0);
    mCallbacks.push_back(mMenuToPlay);
    mCallbacks.push_back(mExitFromMenu);

    setCallbacks(mCallbacks);

    std::cout << "entering MainMenuState" << std::endl;

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