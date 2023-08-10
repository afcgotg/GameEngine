#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "StateParser.h"
#include <cstring>


const std::string PauseState::mPauseID = "PAUSE";

void PauseState::s_pauseToMain(){
    TheGameStateMachine::Instance()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay(){
    TheGameStateMachine::Instance()->popState();
}

void PauseState::update(){
    for(uint64_t i = 0; i < mGameObjects.size(); i++){
        if(!TheGameStateMachine::Instance()->getStateChanged()){
            mGameObjects[i]->update();
        }else{
            TheGameStateMachine::Instance()->setStateChanged(false);
            break;
        }
    }
}

void PauseState::render(){
    for(uint64_t i = 0; i < mGameObjects.size(); i++){
        mGameObjects[i]->draw();
    }
}

bool PauseState::onEnter(std::string filePath){
    StateParser stateParser;

    std::string fullPath(filePath);
    fullPath += "\\states.xml";

    stateParser.parseState(fullPath, mPauseID, &mGameObjects, &mTextureIDList);

    mCallbacks.push_back(0);
    mCallbacks.push_back(s_pauseToMain);
    mCallbacks.push_back(s_resumePlay);

    setCallbacks(mCallbacks);

    std::cout << "entering PauseState" << std::endl;

    return true;
}

bool PauseState::onExit(){
    for(uint64_t i = 0; i < mTextureIDList.size(); i++){
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);
    }
    return true;
}

std::string PauseState::getStateID() const{
    return mPauseID;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks){
    for(uint64_t i = 0; i < mGameObjects.size(); i++){
        if(dynamic_cast<MenuButton*>(mGameObjects[i])){
            MenuButton* pButton = dynamic_cast<MenuButton*>(mGameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}