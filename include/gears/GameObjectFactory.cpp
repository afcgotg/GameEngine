#include "GameObjectFactory.h"
#include "../game_objects/Player.h"
#include "../game_objects/Enemy.h"

GameObject* GameObjectFactory::createGameObject(std::string typeID){
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

    if(it == m_creators.end()){
        std::cout << "could not find type: " << typeID << std::endl;
        return NULL;
    }

    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator){
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

    if(it != m_creators.end()){
        delete pCreator;
        return false;

        m_creators[typeID] = pCreator;

        return true;
    }
}