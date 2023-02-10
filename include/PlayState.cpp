#include <iostream>

#include "PlayState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update(){

}

void PlayState::render(){

}

bool PlayState::onEnter(){
    std::cout << "entering PlayState" << std::endl;
    return true;
}

bool PlayState::onExit(){
    std::cout << "exiting PlayState" << std::endl;
    return true;
}

std::string PlayState::getStateID() const{
    return s_playID;
}