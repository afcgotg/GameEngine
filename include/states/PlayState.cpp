#include <iostream>

#include "PlayState.h"
#include "../gears/TextureManager.h"
#include "../gears/InputHandler.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../Game.h"
#include "PauseState.h"
#include "GameOverState.h"

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

bool PlayState::onEnter(){
    if(!TheTextureManager::Instance()->load("assets/img/GraveRobber/GraveRobber_idle.png", "player", TheGame::Instance()->getRenderer())){
        return false;
    }
    if(!TheTextureManager::Instance()->load("assets/img/Woodcutter/Woodcutter_idle.png", "enemy", TheGame::Instance()->getRenderer())){
        return false;
    }

    GameObject* player = new Player(new LoaderParams(100, 100, 48, 48, "player"));
    GameObject* enemy = new Enemy(new LoaderParams(300, 100, 48, 48, "enemy"));

    m_gameObjects.push_back(player);
    m_gameObjects.push_back(enemy);
    
    return true;
}

bool PlayState::onExit(){
    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->clean();
    }

    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("player");
    TheTextureManager::Instance()->clearFromTextureMap("enemy");

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

    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();

    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
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