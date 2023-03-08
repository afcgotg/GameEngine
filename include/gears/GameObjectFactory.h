#include <string>
#include <map>

#include "../game_objects/GameObject.h"

#ifndef __GAMEOBJECTFACTORY__
#define __GAMEOBJECTFACTORY__

class BaseCreator{
    public:
        virtual GameObject* createGameObject() const = 0;
        virtual ~BaseCreator(){}
};

class GameObjectFactory{

    public:
        GameObject* createGameObject(std::string typeID);

        bool registerType(std::string typeID, BaseCreator* pCreator);


    private:
        std::map<std::string, BaseCreator*> m_creators;
};

#endif