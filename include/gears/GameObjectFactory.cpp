#include "GameObjectFactory.h"
#include "../game_objects/Player.h"
#include "../game_objects/Enemy.h"

GameObjectFactory* GameObjectFactory::s_pInstance = 0;

GameObjectFactory* GameObjectFactory::Instance(){
    if(s_pInstance == 0){
        s_pInstance = new GameObjectFactory();
    }
    return s_pInstance;
}

GameObjectFactory::~GameObjectFactory()
{
}

GameObject* GameObjectFactory::createGameObject(std::string typeID)
{
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
    if(it == m_creators.end())
    {
        std::cout << "could not find type: " << typeID << std::endl;
        return 0;
    }
    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator)
{
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
    if(it != m_creators.end())
    {
        delete pCreator;
        return false;
    }
    m_creators[typeID] = pCreator;
    return true;
}