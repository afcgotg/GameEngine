#include <string>
#include <map>

#include "../game_objects/GameObject.h"

#ifndef __GAMEOBJECTFACTORY__
#define __GAMEOBJECTFACTORY__

class BaseCreator{
    public:
        virtual ~BaseCreator(){}

        virtual GameObject* createGameObject() const = 0;
};

class GameObjectFactory{

    public:
        static GameObjectFactory* Instance();
        
        ~GameObjectFactory();

        GameObject* createGameObject(std::string typeID);
        bool registerType(std::string typeID, BaseCreator* pCreator);


    private: 
        static GameObjectFactory* s_pInstance;

        GameObjectFactory();
        std::map<std::string, BaseCreator*> m_creators;
};

typedef GameObjectFactory TheGameObjectFacotry;

#endif