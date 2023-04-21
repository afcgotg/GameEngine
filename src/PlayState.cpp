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

const std::string PlayState::s_playID = "PLAY";

void PlayState::update(){

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)){
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }

    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->update();
    }

    if(checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1]))){
        TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
    }
}

void PlayState::render(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }
}

bool PlayState::onEnter(const char* filePath){
    StateParser stateParser;

    char* fullPath;
    fullPath = (char*) calloc(strlen(filePath) + strlen("/states.xml") + 1, sizeof(char));
    strcpy(fullPath, filePath);
    strcat(fullPath, "/states.xml");

    stateParser.parseState(fullPath, s_playID, &m_gameObjects, &m_textureIDList);

    std::cout << "entering PlayState" << std::endl;
    return true;
}

bool PlayState::onExit(){
    for(int i = 0; i < m_textureIDList.size(); i++){
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    return true;
}

std::string PlayState::getStateID() const{
    return s_playID;
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