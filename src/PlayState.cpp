#include <iostream>
#include <cstring>

#include "PlayState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "FileManager.h"

const std::string PlayState::mPlayID = "PLAY";

void PlayState::update(){

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)){
        TheGameStateMachine::Instance()->pushState(new PauseState());
    }

    for(uint64_t i = 0; i < mGameObjects.size(); i++){
        mGameObjects[i]->update();
    }

    if(checkCollision(dynamic_cast<SDLGameObject*>(mGameObjects[0]), dynamic_cast<SDLGameObject*>(mGameObjects[1]))){
        TheGameStateMachine::Instance()->pushState(new GameOverState());
    }
}

void PlayState::render(){
    for(uint64_t i = 0; i < mGameObjects.size(); i++){
        mGameObjects[i]->draw();
    }
}

bool PlayState::onEnter(){
    std::string filePath = TheFileManager::Instance()->GetStatesFilePath();

    StateParser stateParser;
    stateParser.parseState(mPlayID, &mGameObjects, &mTextureIDList);

    return true;
}

bool PlayState::onExit(){
    for(uint64_t i = 0; i < mTextureIDList.size(); i++){
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);
    }

    return true;
}

std::string PlayState::getStateID() const{
    return mPlayID;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1->getPosition().getX() + 12;
    rightA = p1->getPosition().getX() + p1->getWidth() - 12;
    topA = p1->getPosition().getY() + 15;
    bottomA = p1->getPosition().getY() + p1->getHeight();

    leftB = p2->getPosition().getX() + 12;
    rightB = p2->getPosition().getX() + p2->getWidth() - 12;
    topB = p2->getPosition().getY() + 15;
    bottomB = p2->getPosition().getY() + p2->getHeight();

    if(bottomA <= topB){
        return false;
    }
    if(topA >= bottomB){
        return false;
    }
    if(rightA <= leftB){
        return false;
    }
    if(leftA >= rightB){
        return false;
    }

    return true;
    
}