#include "GameObject.h"

GameObject::GameObject(){
}

GameObject::~GameObject(){
}

void GameObject::draw(){
    std::cout << "draw game object" << std::endl;
}
void GameObject::update(){
    std::cout << "update game object" << std::endl;
}
void GameObject::clean(){
    std::cout << "clean game object" << std::endl;
}