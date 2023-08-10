#include "GameStateMachine.h"
#include "Game.h"

#include <iostream>
#include <cstring>

GameStateMachine* GameStateMachine::mpInstance = nullptr;
std::vector<GameState*> GameStateMachine::mGameStates;

GameStateMachine* GameStateMachine::Instance()
{
    if(mpInstance == nullptr)
        mpInstance = new GameStateMachine();
    return mpInstance;
}

void GameStateMachine::pushState(GameState* pState){
    mGameStates.push_back(pState);

    std::string assetsPath(TheGame::Instance()->GetExecutionPath());

    assetsPath += "\\assets";

    mGameStates.back()->onEnter(assetsPath);
}

void GameStateMachine::changeState(GameState* pState){
    if(!mGameStates.empty()){
        if(mGameStates.back()->getStateID() == pState->getStateID()){
            return; // do nothing
        }
        GameStateMachine::popState();
    }
    GameStateMachine::pushState(pState);
}

void GameStateMachine::popState(){
    if(!mGameStates.empty()){
        if(mGameStates.back()->onExit()){
            //delete mGameStates.back();
            mGameStates.pop_back();
        }
    }
}

void GameStateMachine::update(){
    if(!mGameStates.empty()){
        mGameStates.back()->update();
    }
}

void GameStateMachine::render(){
    if(!mGameStates.empty()){
        mGameStates.back()->render();
    }
}

void GameStateMachine::setStateChanged(bool change){
    mStateChanged = change;
}

bool GameStateMachine::getStateChanged(){return mStateChanged;}